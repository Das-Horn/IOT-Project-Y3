import React from "react";
import styles from '../SCSS/Cards.module.scss';

export default class Intro extends React.Component {
    render() {
        return(
            <div className={styles.Card}>
                {this.props.children}
            </div>
        );
    }
}