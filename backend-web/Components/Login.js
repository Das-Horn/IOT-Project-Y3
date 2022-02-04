import React from "react";
import styles from "../SCSS/Login.module.scss";

export default class Login extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            error : null,
            LoggedIn : false
        }
        this.handleClick = this.handleClick.bind(this);
    }

    handleClick(){
        const UName = document.querySelector('#UName').value;
        const Pass = document.querySelector('#Pass').value;

        if(UName == '' || Pass == ''){
            this.setState({
                error : "Please enter valid values."
            });
        }else{
            fetch(`/api/Login/${UName}/${Pass}`)
            .then(
                (res) => {
                    if(res.status == 200){
                        this.setState({
                            LoggedIn : true
                        });
                    }else if(res.status == 500){
                        this.setState({
                            error : res.body['error']
                        });
                    }
                }
            )
        }
    }

    render(){
        if(this.state.LoggedIn){
            return(<div></div>);
        }else{
            return(
                <div className={styles.Login}>
                    <div className={styles.LoginCont}>
                        <h1>Login</h1>
                        <input id="UName" placeholder="Username"></input>
                        <input type="password" id="Pass" placeholder="Password"></input>
                        {this.state.error != null ? <p>{this.state.error}</p> : ''}
                        <button onClick={this.handleClick}>Submit</button>
                    </div>    
                </div>
            );
        }
    }
}