import React from "react";
import styles from "../SCSS/Login.module.scss";

export default class Login extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            error : null
        }
    }

    render(){
        return(
            <div className={styles.Login}>
                <div className={styles.LoginCont}>
                    <h1>Login</h1>
                    <input id="UName" placeholder="Username"></input>
                    <input id="Pass" placeholder="Password"></input>
                    {this.state.error != null ? <p>{this.state.error}</p> : ''}
                    <button>Submit</button>
                </div>    
            </div>
        );
    }
}