import React from "react";
import styles from "../SCSS/Header.module.scss"

export default class Header extends React.Component {
    render(){
        return(
            <div className={styles.Frame}>
                <h1>Smart Home Systems</h1>
            </div>
        );
    }
}