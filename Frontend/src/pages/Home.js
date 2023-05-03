import React, { useState, useEffect } from "react"
import styled from 'styled-components';
import { Popup } from "semantic-ui-react";
import Axios from 'axios'

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
    const options = ['Enumerator', 'Counter'];

    const [active, setActive] = useState('');
    const [option, setOption] = useState('');
    const [mValue, setMValue] = useState("");
    const [nValue, setNValue] = useState("");
    const [kValue, setKValue] = useState("");
    const [result, setResult] = useState("");

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
        if (option === "Enumerator") {
            return (
                <div className= "Warning">
                    <p>
                        Once "Generate" button is pressed a .txt file will be downloaded.
                    </p>
                    <p>
                        This file will include all the partitions.
                    </p>
                    <p>
                        The file can also be opened with Microsoft Excel!
                    </p>
                </div>
            );
        }
    }

    useEffect(() => {
        setMValue("");
        setNValue("");
        setKValue("");
        setResult("");
    }, [active]);

    const generate = () => {
        if (active === "Rogers Ramanujan" && option === "Counter") {
            Axios.post("http://localhost:3001/RogersRamanujanCounter", {
                nValue: nValue,  
                mValue: mValue,
            }).then((response)=> {
                console.log(response);
                setResult("There are "+ response.data.message +" partitions!");
            });
        } else if (active === "Rogers Ramanujan Gordon" && option === "Counter") {
            Axios.post("http://localhost:3001/RogersRamanujanGordonCounter", {
                nValue: nValue,  
                mValue: mValue,
                kValue: kValue,
            }).then((response)=> {
                console.log(response);
                setResult("There are "+ response.data.message +" partitions!");
            });
        } else if (active === "Rogers Ramanujan Gordon" && option === "Enumerator") {
            Axios.post("http://localhost:3001/RogersRamanujanGordonEnumeration", {
                nValue: nValue,  
                mValue: mValue,
                kValue: kValue,
            }).then((response)=> {
                const fileData = JSON.stringify(response.data.data);
                const blob = new Blob([fileData], { type: "text/plain" });
                const url = URL.createObjectURL(blob);
                const link = document.createElement("a");
                link.download = "partitions.txt";
                link.href = url;
                link.click();
                setResult(response.data.message);
            });
        } else if (active === "Rogers Ramanujan" && option === "Enumerator") {
            Axios.post("http://localhost:3001/RogersRamanujanEnumeration", {
                nValue: nValue,  
                mValue: mValue,
            }).then((response)=> {
                let fileData = JSON.stringify(response.data.data);
                fileData = fileData.slice(1, -2);
                const blob = new Blob([fileData], { type: "text/plain" });
                const url = URL.createObjectURL(blob);
                const link = document.createElement("a");
                link.download = "partitions.txt";
                link.href = url;
                link.click();
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
                        <input type="text" value = {mValue} onChange={(e) => setMValue(e.target.value)} placeholder = "Write the value of m here!" />
                        <input type="text" value = {nValue} onChange={(e) => setNValue(e.target.value)} placeholder = "Write the value of n here!" />
                        </div>
                    )
                } else if (active === "Rogers Ramanujan Gordon" && option.length !== 0) {
                    return (
                        <div className = "Roger Ramanujan Gordon">
                        <input type="text" value = {mValue} onChange={(e) => setMValue(e.target.value)} placeholder = "Write the value of m here!" />
                        <input type="text" value = {nValue} onChange={(e) => setNValue(e.target.value)} placeholder = "Write the value of n here!" />
                        <input type="text" value = {kValue} onChange={(e) => setKValue(e.target.value)} placeholder = "Write the value of k here!" />
                        </div>
                    )
                } else if (active === "Capparelli's Identity" && option.length !== 0) {
                    return (
                        <div className = "Capparelli\'s Identity">
                        <input type="text" value = {mValue} onChange={(e) => setMValue(e.target.value)} placeholder = "Write the value of m here!" />
                        <input type="text" value = {nValue} onChange={(e) => setNValue(e.target.value)} placeholder = "Write the value of n here!" />
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
                "Partionerator" is a web application that enables users to efficiently generate a range of partition (Rogers Ramanujan, Rogers Ramanujan Gordon, Capparelli's Identity and X) enumeration and counting methods. 
            </Popup>
        </div>
    );
}