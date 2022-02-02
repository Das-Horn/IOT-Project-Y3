import React from "react";
import styles from "../SCSS/Header.module.scss"

export default class Header extends React.Component {
    render(){
        return(
            <div className={styles.Frame}>
                <h1>Smart Systems Home</h1>
                <p>A project by Ben Stobie, Craig Doyle, Jason Leonard , Redas Strumila</p>
            </div>
        );
    }
}