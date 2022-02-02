import Head from 'next/head'
import Header from '../Components/Header'
import Intro from '../Components/Intro'


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
            <p>Sorry you seem to not have an internet connection right now please try again later.</p>
            <p style={{textAlign : "center"}}>(￣o￣) . z Z</p>
          </Intro>
      </div>
    </div>
  )
}
