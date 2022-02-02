import Head from 'next/head'
import Header from '../Components/Header'
import Intro from '../Components/Intro'
import Button from '../Components/Button'
import Tgl from '../Components/ToggleInd'
import Graph from '../Components/Graph'

export default function Home() {
  return (
    <div className="container">
      <Head>
        <title>Create Next App</title>
        <link rel="icon" href="/favicon.ico" />
        <link rel="stylesheet" type="text/css" href="main.css " />
        <link rel="manifest" href="/manifest.json" />
        <meta name='theme-color' content='#61A6AB'/>
        <script src='scripts.js' />
      </Head>
      <Header />
      <div className='contents'>
        <Intro />
        <Button sensID={4}>Security System</Button>
        <div>
          <Tgl sensID={4} api={'Request/jobs'} initState={false}>Security System</Tgl>
          {/* <Tgl initState={true}>Ben is a big dumb idiot</Tgl> */}
          {/* <Tgl>BabaBooey</Tgl> */}
        </div>
        {/* <Graph xTag={"Requests/Data"} MCDat={"Requests/MCList"} /> */}
      </div>
    </div>
  )
}
