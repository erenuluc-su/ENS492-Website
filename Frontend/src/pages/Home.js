import React, { useState, useEffect } from "react"
import styled from 'styled-components';
import { Popup } from "semantic-ui-react";
import Axios from 'axios'
import * as FileSaver from 'file-saver'
import XLSX from 'sheetjs-style'
export const Home = (props) => {

    const Button = styled.button``;

    const ButtonToggle = styled(Button)`
        opacity: 0.6;
        ${({ active }) => active && `opacity: 1;`}
    `;

    const ButtonGroup = styled.div`
        display: flex;
    `;

    const partitions = ['Rogers Ramanujan', 'Rogers Ramanujan Gordon', 'Capparelli\'s Identity'];
    const options = ['Generator', 'Counter'];

    const [active, setActive] = useState('');
    const [option, setOption] = useState('');
    const [mValue, setMValue] = useState("");
    const [nValue, setNValue] = useState("");
    const [kValue, setKValue] = useState("");
    const [result, setResult] = useState("");
    const [file, setFile] = useState("");
    const [format, setFormat] = useState(false);

    const fileType = 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet;charset=UTF-8';
    const fileExtension = '.xlsx';

    function ToggleGroupPartitions() {
        return (
          <p>
            {partitions.map(type => (
              <ButtonToggle
                key={type}
                active={active === type}
                onClick={() => setActive(type)}
              >
                {type}
              </ButtonToggle>
            ))}
          </p>
        );
    }

    function ToggleGroupOptions() {
        if (active.length !== 0) {
            return (
                <div className= "Option">
                    <p>
                        {options.map(type => (
                        <ButtonToggle
                            key={type}
                            active={option === type}
                            onClick={() => setOption(type)}
                        >
                            {type}
                        </ButtonToggle>
                        ))}
                    </p>
                </div>
            );
        }
    }

    function Warning() {
        return (
            <div className = "Warning">
                <div>
                    {(() => {
                    if (active === "Rogers Ramanujan Gordon" && option.length !== 0 && (mValue === "" || nValue === "" || kValue === "")) {
                        return (
                            <p>
                                Please enter an integer for every input value!
                            </p>
                        )
                    } else if ((active === "Rogers Ramanujan" || active === "Capparelli's Identity") && option.length !== 0 && (mValue === "" || nValue === "")) {
                        return (
                            <p>
                                Please enter an integer for every input value!
                            </p>
                        )
                    } else if (file === "" && active !== "" && option !== "") {
                        return (
                            <p>
                                Please select a file type!
                            </p>
                        )
                    }
                    })()}
                </div>
            </div>
        )
    }

    useEffect(() => {
        setMValue("");
        setNValue("");
        setKValue("");
        setResult("");
        setFile("");
        setFormat(false);
    }, [active]);

    const onOptionChange = e => {
        setFile(e.target.value)
    }

    const ec = (r, c) => {
        return XLSX.utils.encode_cell({r:r,c:c})
    }
    
    const delete_row = (ws, row_index) => {
        let range = XLSX.utils.decode_range(ws["!ref"])
        for(var R = row_index; R < range.e.r; ++R){
            for(var C = range.s.c; C <= range.e.c; ++C){
                ws[ec(R, C)] = ws[ec(R+1, C)]
            }
        }
        range.e.r--
        ws['!ref'] = XLSX.utils.encode_range(range.s, range.e)
    }

    const generate = () => {
        if (active === "Rogers Ramanujan" && option === "Counter" && (mValue !== "" && nValue !== "")) {
            Axios.post("http://localhost:3001/RogersRamanujanCounter", {
                nValue: nValue,  
                mValue: mValue,
                file: file,
            }).then((response)=> {
                console.log(response);
                if (file === "text") {
                    let fileData = JSON.stringify(response.data.data);
                    fileData = fileData.replace(/,/g, '\n');
                    fileData = fileData.replace(/;/g, ' ');
                    fileData = fileData.replace(/\[/g, '');
                    fileData = fileData.replace(/]/g, '');
                    fileData = fileData.replace(/"/g, '');
                    const blob = new Blob([fileData], { type: "text/plain" });
                    const url = URL.createObjectURL(blob);
                    const link = document.createElement("a");
                    link.download = "partitions.txt";
                    link.href = url;
                    link.click();
                }
                else {
                    let ws = XLSX.utils.json_to_sheet(response.data.data);
                    delete_row(ws, 0);
                    const wb = { Sheets: { 'data': ws }, SheetNames: ['data']};
                    const excelBuffer = XLSX.write(wb, { bookType: 'xlsx', type: 'array'});
                    const data = new Blob([excelBuffer], { type: fileType });
                    FileSaver.saveAs(data, 'partitions' + fileExtension);
                }
                setResult("There are "+ response.data.message +" partitions!");
            });
        } else if (active === "Rogers Ramanujan Gordon" && option === "Counter" && (mValue !== "" && nValue !== "" && kValue !== "")) {
            Axios.post("http://localhost:3001/RogersRamanujanGordonCounter", {
                nValue: nValue,  
                mValue: mValue,
                kValue: kValue,
                file: file,
            }).then((response)=> {
                console.log(response);
                if (file === "text") {
                    let fileData = JSON.stringify(response.data.data);
                    fileData = fileData.replace(/,/g, '\n');
                    fileData = fileData.replace(/;/g, ' ');
                    fileData = fileData.replace(/\[/g, '');
                    fileData = fileData.replace(/]/g, '');
                    fileData = fileData.replace(/"/g, '');
                    const blob = new Blob([fileData], { type: "text/plain" });
                    const url = URL.createObjectURL(blob);
                    const link = document.createElement("a");
                    link.download = "partitions.txt";
                    link.href = url;
                    link.click();
                }
                else {
                    let ws = XLSX.utils.json_to_sheet(response.data.data);
                    delete_row(ws, 0);
                    const wb = { Sheets: { 'data': ws }, SheetNames: ['data']};
                    const excelBuffer = XLSX.write(wb, { bookType: 'xlsx', type: 'array'});
                    const data = new Blob([excelBuffer], { type: fileType });
                    FileSaver.saveAs(data, 'partitions' + fileExtension);
                }
                setResult("There are "+ response.data.message +" partitions!");
            });
        } else if (active === "Rogers Ramanujan Gordon" && option === "Generator" && (mValue !== "" && nValue !== "" && kValue !== "") 
            && file !== "") {
            Axios.post("http://localhost:3001/RogersRamanujanGordonEnumeration", {
                nValue: nValue,  
                mValue: mValue,
                kValue: kValue,
                file: file,
                format: format,
            }).then((response)=> {
                console.log(response);
                if (file === "text") {
                    let fileData = JSON.stringify(response.data.data);
                    fileData = fileData.replace(/,/g, '\n');
                    fileData = fileData.replace(/;/g, ' ');
                    fileData = fileData.replace(/\[/g, '');
                    fileData = fileData.replace(/]/g, '');
                    fileData = fileData.replace(/"/g, '');
                    const blob = new Blob([fileData], { type: "text/plain" });
                    const url = URL.createObjectURL(blob);
                    const link = document.createElement("a");
                    link.download = "partitions.txt";
                    link.href = url;
                    link.click();
                }
                else {
                    let ws = XLSX.utils.json_to_sheet(response.data.data);
                    delete_row(ws, 0);
                    const wb = { Sheets: { 'data': ws }, SheetNames: ['data']};
                    const excelBuffer = XLSX.write(wb, { bookType: 'xlsx', type: 'array'});
                    const data = new Blob([excelBuffer], { type: fileType });
                    FileSaver.saveAs(data, 'partitions' + fileExtension);
                }
                setResult(response.data.message);
            });
        } else if (active === "Rogers Ramanujan" && option === "Generator" && (mValue !== "" && nValue !== "") && file !== "") {
            Axios.post("http://localhost:3001/RogersRamanujanEnumeration", {
                nValue: nValue,  
                mValue: mValue,
                file: file,
                format: format,
            }).then((response)=> {
                console.log(response);
                if (file === "text") {
                    let fileData = JSON.stringify(response.data.data);
                    fileData = fileData.replace(/,/g, '\n');
                    fileData = fileData.replace(/;/g, ' ');
                    fileData = fileData.replace(/\[/g, '');
                    fileData = fileData.replace(/]/g, '');
                    fileData = fileData.replace(/"/g, '');
                    const blob = new Blob([fileData], { type: "text/plain" });
                    const url = URL.createObjectURL(blob);
                    const link = document.createElement("a");
                    link.download = "partitions.txt";
                    link.href = url;
                    link.click();
                }
                else {
                    let ws = XLSX.utils.json_to_sheet(response.data.data);
                    delete_row(ws, 0);
                    const wb = { Sheets: { 'data': ws }, SheetNames: ['data']};
                    const excelBuffer = XLSX.write(wb, { bookType: 'xlsx', type: 'array'});
                    const data = new Blob([excelBuffer], { type: fileType });
                    FileSaver.saveAs(data, 'partitions' + fileExtension);
                }
                setResult(response.data.message);
            });
        } else if (active === "Capparelli's Identity" && option === "Counter" && (mValue !== "" && nValue !== "") && file !== "") {
            Axios.post("http://localhost:3001/CapparelliCounter", {
                nValue: nValue,  
                mValue: mValue,
                file: file,
            }).then((response)=> {
                console.log(response);
                if (file === "text") {
                    let fileData = JSON.stringify(response.data.data);
                    fileData = fileData.replace(/,/g, '\n');
                    fileData = fileData.replace(/;/g, ' ');
                    fileData = fileData.replace(/\[/g, '');
                    fileData = fileData.replace(/]/g, '');
                    fileData = fileData.replace(/"/g, '');
                    const blob = new Blob([fileData], { type: "text/plain" });
                    const url = URL.createObjectURL(blob);
                    const link = document.createElement("a");
                    link.download = "partitions.txt";
                    link.href = url;
                    link.click();
                }
                else {
                    let ws = XLSX.utils.json_to_sheet(response.data.data);
                    delete_row(ws, 0);
                    const wb = { Sheets: { 'data': ws }, SheetNames: ['data']};
                    const excelBuffer = XLSX.write(wb, { bookType: 'xlsx', type: 'array'});
                    const data = new Blob([excelBuffer], { type: fileType });
                    FileSaver.saveAs(data, 'partitions' + fileExtension);
                }
                setResult("There are "+ response.data.message +" partitions!");
            });
        } else if (active === "Capparelli's Identity" && option === "Generator" && (mValue !== "" && nValue !== "") && file !== "") {
            Axios.post("http://localhost:3001/CapparelliEnumeration", {
                nValue: nValue,  
                mValue: mValue,
                file: file,
                format: format,
            }).then((response)=> {
                console.log(response);
                if (file === "text") {
                    let fileData = JSON.stringify(response.data.data);
                    fileData = fileData.replace(/,/g, '\n');
                    fileData = fileData.replace(/;/g, ' ');
                    fileData = fileData.replace(/\[/g, '');
                    fileData = fileData.replace(/]/g, '');
                    fileData = fileData.replace(/"/g, '');
                    const blob = new Blob([fileData], { type: "text/plain" });
                    const url = URL.createObjectURL(blob);
                    const link = document.createElement("a");
                    link.download = "partitions.txt";
                    link.href = url;
                    link.click();
                }
                else {
                    let ws = XLSX.utils.json_to_sheet(response.data.data);
                    delete_row(ws, 0);
                    const wb = { Sheets: { 'data': ws }, SheetNames: ['data']};
                    const excelBuffer = XLSX.write(wb, { bookType: 'xlsx', type: 'array'});
                    const data = new Blob([excelBuffer], { type: fileType });
                    FileSaver.saveAs(data, 'partitions' + fileExtension);
                }
                setResult(response.data.message);
            });
        }
    };

    return (
        <div className = "Partionerator">
            <h1>WELCOME TO Partionerator</h1>
            <ToggleGroupPartitions />
            <ToggleGroupOptions />
            <div>
                {(() => {
                if (active === "Rogers Ramanujan" && option.length !== 0) {
                    return (
                        <div className = "Rogers Ramanujan">
                        <input type="text" value = {mValue} onChange={(e) => setMValue(e.target.value)} 
                            placeholder = "Write the value of m here!" />
                        <input type="text" value = {nValue} onChange={(e) => setNValue(e.target.value)} 
                            placeholder = "Write the value of n here!" />
                        </div>
                    )
                } else if (active === "Rogers Ramanujan Gordon" && option.length !== 0) {
                    return (
                        <div className = "Roger Ramanujan Gordon">
                        <input type="text" value = {mValue} onChange={(e) => setMValue(e.target.value)} 
                            placeholder = "Write the value of m here!" />
                        <input type="text" value = {nValue} onChange={(e) => setNValue(e.target.value)} 
                            placeholder = "Write the value of n here!" />
                        <input type="text" value = {kValue} onChange={(e) => setKValue(e.target.value)} 
                            placeholder = "Write the value of k here!" />
                        </div>
                    )
                } else if (active === "Capparelli's Identity" && option.length !== 0) {
                    return (
                        <div className = "Capparelli\'s Identity">
                        <input type="text" value = {mValue} onChange={(e) => setMValue(e.target.value)} 
                            placeholder = "Write the value of m here!" />
                        <input type="text" value = {nValue} onChange={(e) => setNValue(e.target.value)} 
                            placeholder = "Write the value of n here!" />
                        </div>
                    )
                }
                })()}
            </div>
            <div>
                {(() => {
                if (option === "Generator") {
                    return (
                        <div className = "Format">
                            <div>
                                <input className = "radioinput" type="radio" value="excel" name="file" checked={file === "excel"}
                                    onChange={onOptionChange} id="excel"/>
                                <label htmlFor="excel">Excel File</label>
                            </div>
                            <div>
                                <input className = "radioinput" type="radio" value="text" name="file" checked={file === "text"}
                                    onChange={onOptionChange} id="text"/>
                                <label htmlFor="text">Text File</label>
                            </div>
                            <div>
                                <input className = "radioinput" type="checkbox" checked={format}
                                    onChange={() => setFormat((prev) => !prev)}/>
                                <label htmlFor="multiple">Seperate part of partitions</label>
                            </div>
                        </div>
                    )
                } 
                else if (option === "Counter") {
                    return (
                        <div className = "NoFormat">
                            <div>
                                <input className = "radioinput" type="radio" value="excel" name="file" checked={file === "excel"}
                                    onChange={onOptionChange} id="excel"/>
                                <label htmlFor="excel">Excel File</label>
                            </div>
                            <div>
                                <input className = "radioinput" type="radio" value="text" name="file" checked={file === "text"}
                                    onChange={onOptionChange} id="text"/>
                                <label htmlFor="text">Text File</label>
                            </div>
                        </div>
                    )
                }
                })()}
            </div>
            <div>
                {(() => {
                if (active.length !== 0 && option.length !== 0) {
                    return (
                        <div className = "Generate">
                        <Button onClick={generate}> Generate </Button>
                        </div>
                    )
                } else {
                    return (
                        <div className = "NoGenerate">
                        </div>
                    )
                }
                })()}
            </div>
            <Warning />
            <div> {result} </div>
            <Popup
                trigger={<child-btns>Info</child-btns>}
                position = "top left"
                style={{ color: 'white' }}
            >
                "Partionerator" is a web application that enables users to efficiently generate a range of partition 
                (Rogers Ramanujan, Rogers Ramanujan Gordon, Capparelli's Identity and X) enumeration and counting methods. 
            </Popup>
        </div>
    );
}