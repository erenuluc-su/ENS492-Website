import React, { useState } from "react"
import { useHistory} from "react-router-dom";
import styled from 'styled-components';

export const Home = (props) => {

    let history = useHistory();

    const types = ['Roger Ramanujan', 'Roger Ramanujan Gordon', 'Capparelli\'s Identity'];

    const Button = styled.button``;

    const ButtonToggle = styled(Button)`
        opacity: 0.6;
        ${({ active }) => active && `opacity: 1;`}
    `;

    const ButtonGroup = styled.div`
        display: flex;
    `;

    const [active, setActive] = useState(types[0]);
    const [mValue, setMValue] = useState("");
    const [nValue, setNValue] = useState("");
    const [kValue, setKValue] = useState("");

    function ToggleGroup() {
        return (
          <ButtonGroup>
            {types.map(type => (
              <ButtonToggle
                key={type}
                active={active === type}
                onClick={() => setActive(type)}
              >
                {type}
              </ButtonToggle>
            ))}
          </ButtonGroup>
        );
    }

    function Inside() {
        if (active === "Roger Ramanujan"){
            return (
                <div className = "Roger Ramanujan">
                    <input value = {mValue} onChange={(e) => setMValue(e.target.value)} placeholder = "Write value of m here" />
                    <input value = {nValue} onChange={(e) => setNValue(e.target.value)} placeholder = "Write value of n here" />
                </div>
            );
        }
        else if (active === "Roger Ramanujan Gordon"){
            return (
                <div className = "Roger Ramanujan Gordon">
                    <input value = {mValue} onChange={(e) => setMValue(e.target.value)} placeholder = "Write value of m here" />
                    <input value = {nValue} onChange={(e) => setNValue(e.target.value)} placeholder = "Write value of n here" />
                    <input value = {kValue} onChange={(e) => setKValue(e.target.value)} placeholder = "Write value of k here" />
                </div>
            );
        }
        if (active === "Capparelli\'s Identity"){
            return (
                <div className = "Capparelli\'s Identity">
                    <input value = {mValue} onChange={(e) => setMValue(e.target.value)} placeholder = "Write value of m here" />
                    <input value = {nValue} onChange={(e) => setNValue(e.target.value)} placeholder = "Write value of n here" />
                </div>
            );
        }
    }

    return (
        <div className = "Partionerator">
            <h1>WELCOME TO Partionerator</h1>
            <ToggleGroup />
            <Inside />
        </div>
    );
}