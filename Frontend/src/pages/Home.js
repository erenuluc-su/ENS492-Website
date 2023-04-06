import React, { useState } from "react"
import { useHistory} from "react-router-dom";

export const Home = (props) => {

    let history = useHistory();

    const partitions = ['Roger Ramanujan', 'Roger Ramanujan Gordon', 'Capparelli\'s Identity'];
    const options = ['Enumerator', 'Counter'];

    const [active, setActive] = useState('');
    const [option, setOption] = useState('');
    const [mValue, setMValue] = useState("");
    const [nValue, setNValue] = useState("");
    const [kValue, setKValue] = useState("");

    function ToggleGroupPartitions() {
        return (
          <p>
            {partitions.map(type => (
              <button
                key={type}
                active={active === type}
                onClick={() => setActive(type)}
              >
                {type}
              </button>
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
                        <button
                            key={type}
                            active={option === type}
                            onClick={() => setOption(type)}
                        >
                            {type}
                        </button>
                        ))}
                    </p>
                </div>
            );
        }
    }

    return (
        <div className = "Partionerator">
            <h1>WELCOME TO Partionerator</h1>
            <ToggleGroupPartitions />
            <ToggleGroupOptions />
            <div>
                {(() => {
                if (active === "Roger Ramanujan" && option.length !== 0) {
                    return (
                        <div className = "Roger Ramanujan">
                        <input type="text" value = {mValue} onChange={(e) => setMValue(e.target.value)} placeholder = "Write the value of m here!" />
                        <input type="text" value = {nValue} onChange={(e) => setNValue(e.target.value)} placeholder = "Write the value of n here!" />
                        </div>
                    )
                } else if (active === "Roger Ramanujan Gordon" && option.length !== 0) {
                    return (
                        <div className = "Roger Ramanujan Gordon">
                        <input type="text" value = {mValue} onChange={(e) => setMValue(e.target.value)} placeholder = "Write the value of m here!" />
                        <input type="text" value = {nValue} onChange={(e) => setNValue(e.target.value)} placeholder = "Write the value of n here!" />
                        <input type="text" value = {kValue} onChange={(e) => setKValue(e.target.value)} placeholder = "Write the value of k here!" />
                        </div>
                    )
                } else if (active === "Capparelli\'s Identity" && option.length !== 0) {
                    return (
                        <div className = "Capparelli\'s Identity">
                        <input type="text" value = {mValue} onChange={(e) => setMValue(e.target.value)} placeholder = "Write the value of m here!" />
                        <input type="text" value = {nValue} onChange={(e) => setNValue(e.target.value)} placeholder = "Write the value of n here!" />
                        </div>
                    )
                }
                })()}
            </div>
        </div>
    );
}