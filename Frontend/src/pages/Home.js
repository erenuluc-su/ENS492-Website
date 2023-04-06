import React, { useState } from "react"
import { useHistory} from "react-router-dom";
import styled from 'styled-components';

export const Home = (props) => {

    let history = useHistory();

    const partitions = ['Roger Ramanujan', 'Roger Ramanujan Gordon', 'Capparelli\'s Identity'];
    const options = ['Enumerator', 'Counter'];

    const Button = styled.button``;

    const ButtonToggle = styled(Button)`
        opacity: 0.6;
        ${({ active }) => active && `opacity: 1;`}
    `;

    const ButtonGroup = styled.div`
        display: flex;
    `;

    const [active, setActive] = useState('');
    const [option, setOption] = useState('');
    const [mValue, setMValue] = useState("");
    const [nValue, setNValue] = useState("");
    const [kValue, setKValue] = useState("");

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

    function Inputs() {
        if (active === "Roger Ramanujan" && option.length !== 0){
            return (
                <div className = "Roger Ramanujan">
                    <input value = {mValue} onChange={(e) => setMValue(e.target.value)} placeholder = "Write the value of m here!" />
                    <input value = {nValue} onChange={(e) => setNValue(e.target.value)} placeholder = "Write the value of n here!" />
                </div>
            );
        }
        else if (active === "Roger Ramanujan Gordon" && option.length !== 0){
            return (
                <div className = "Roger Ramanujan Gordon">
                    <input value = {mValue} onChange={(e) => setMValue(e.target.value)} placeholder = "Write the value of m here!" />
                    <input value = {nValue} onChange={(e) => setNValue(e.target.value)} placeholder = "Write the value of n here!" />
                    <input value = {kValue} onChange={(e) => setKValue(e.target.value)} placeholder = "Write the value of k here!" />
                </div>
            );
        }
        if (active === "Capparelli\'s Identity" && option.length !== 0){
            return (
                <div className = "Capparelli\'s Identity">
                    <input value = {mValue} onChange={(e) => setMValue(e.target.value)} placeholder = "Write the value of m here!" />
                    <input value = {nValue} onChange={(e) => setNValue(e.target.value)} placeholder = "Write the value of n here!" />
                </div>
            );
        }
    }

    return (
        <div className = "Partionerator">
            <h1>WELCOME TO Partionerator</h1>
            <ToggleGroupPartitions />
            <ToggleGroupOptions />
            <Inputs />
        </div>
    );
}