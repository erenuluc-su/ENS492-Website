import React from "react"
import { useHistory} from "react-router-dom";

export const Home = (props) => {

    let history = useHistory();

    return (
        <div className = "auth-form-container">
            <h2>WELCOME TO Partionerator</h2>
        </div>
    );
}