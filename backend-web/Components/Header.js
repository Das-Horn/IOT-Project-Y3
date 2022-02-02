import React from "react";
import Image from "next/image"
import styles from "../SCSS/Header.module.scss"

export default class Header extends React.Component {
    render(){
        return(
            <div className={styles.Frame}>
                <div style={{display : "flex"}}>
                    <div className={styles.IconCont}>
                        <Image 
                            src="/icons/icon_512x512.png"
                            layout="responsive"
                            alt="Icon"
                            width={45}
                            height={45}
                        />
                    </div>
                    <h1>Smart Systems Home</h1>
                </div>
                <p>A project by Ben Stobie, Craig Doyle, Jason Leonard , Redas Strumila</p>
            </div>
        );
    }
}