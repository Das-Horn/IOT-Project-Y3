import Head from 'next/head'
import Header from '../Components/Header'
import Intro from '../Components/Intro'
import Button from '../Components/Button'
import Tgl from '../Components/ToggleInd'

export default function Home() {
  return (
    <div className="container">
      <Head>
        <title>Create Next App</title>
        <link rel="icon" href="/favicon.ico" />
        <link rel="stylesheet" type="text/css" href="main.css " />
        <script src='scripts.js' />
      </Head>
      <Header />
      <div className='contents'>
        <Intro />
        <Button>Testing</Button>
        <div>
          <Tgl sensID={4} api={'Request/jobs'} initState={false}>Testing</Tgl>
          {/* <Tgl initState={true}>Ben is a big dumb idiot</Tgl> */}
          {/* <Tgl>BabaBooey</Tgl> */}
        </div>
      </div>
    </div>
  )
}
