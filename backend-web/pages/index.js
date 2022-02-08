import Head from 'next/head'
import Header from '../Components/Header'
import Intro from '../Components/Intro'
import Button from '../Components/Button'
import Tgl from '../Components/ToggleInd'
import Graph from '../Components/Graph'
import Login from '../Components/Login'
import HomePage from '../Components/HomePage'
import Link from 'next/link'

export default function Home() {
  return (
    <div className="container">
      <Head>
        <title>Smart Systems Home</title>
        <link rel="icon" href="/icons/icon_512x512.png" />
        <link rel="stylesheet" type="text/css" href="main.css " />
        <link rel="manifest" href="/manifest.json" />
        <link rel="image/png" href='/icons/icon_512x512.png' />
        <meta name='theme-color' content='#61A6AB'/>
        <meta name="viewport" content="width=device-width, initial-scale=1.0" /> 
      </Head>
      <Header />
      <div className='contents'>
        <Intro>
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
                <Link href="/Home">
                  <a>Stats Page</a>
                </Link>
        </Intro>
        <Login />
      </div>
    </div>
  )
}
