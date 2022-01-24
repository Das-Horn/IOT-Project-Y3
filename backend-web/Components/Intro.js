import React from "react";
import styles from '../SCSS/Intro.module.scss';

export default class Intro extends React.Component {
    render() {
        return(
            <div className={styles.IntroFrame}>
                <p>This is a project that is developed by Craig Doyle, Redas Strumila Jason Leonard and Ben Stobie. This project is a centralized smart home system for monitoring and controling various systems inside of the household. This system is capable of monitoring of:</p>
                <ul>
                    <li>Tempature</li>
                    <li>Humidity</li>
                    <li>C02 Detection</li>
                    <li>Sound Detection</li>
                    <li>Shock Detection</li>
                    <li>Motion Detection</li>
                </ul>
                <p>The system is also capable of controlling multiple elements of the household, such as:</p>
                <ul>
                    <li>Door Locks</li>
                    <li>Oven Tempature</li>
                    <li>Lights</li>
                </ul>
            </div>
        );
    }
}