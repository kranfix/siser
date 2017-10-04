package main

import (
  "fmt"
  "time"
  "bytes"
  "net/http"
  "encoding/binary"
  "github.com/kranfix/siser/siser"
  "github.com/tarm/serial"
)

func main(){
  // Reserving memory for SISER Dataframe
  sDt := siser.SiserDataframe{}//  // Opening Serial Port

  // Opening  Serial Port
  c := &serial.Config{
    Name: "/dev/ttyACM0",
    Baud: 9600,
    ReadTimeout: 100 * time.Millisecond,
  }
  s, err := serial.OpenPort(c)
  if err != nil {
    fmt.Println(err)
    return
  }
  fmt.Println("Serialport: Opened")
  defer func() {
    s.Close()
    fmt.Println("Serialport: Closed")
  }()
  err = s.Flush()
  if err != nil {
    return
  }

  // Dataframe Lecture
  initialDataframe := []byte("OPEN")
  onebyte := make([]byte, 1)

  // Counts the number of blocks to read
  Limit := 4
  for count := 0; count < Limit; count++ { // loop
    // Initial dataframe detection
    for i := 0; i < 4;  {
      _, err := s.Read(onebyte)
      if err != nil {
        continue
      } else if onebyte[0] == initialDataframe[i] {
        i++
        fmt.Printf("%s",onebyte)
      } else {
        i = 0
      }
    }

    fmt.Print(":")
    // Dataframe
    n := binary.Size(sDt)
    B := make([]byte, n)
    n, err := s.Read(B)
    buf := bytes.NewBuffer(B[:])
    //fmt.Printf("% x",B[:n])
    err = binary.Read(buf, binary.LittleEndian, &sDt)
    fmt.Print(sDt)
    if err == nil {
      strbuf := bytes.NewBufferString(sDt.String())
      _, err := http.Post("http://localhost:1880/mongo",
                          "application/json", strbuf)
      if err != nil {
        fmt.Println("Problem with local server")
        fmt.Println(err)
      } else {
        fmt.Println(" ... Mongo ok!")
      }
    }

    for i:=0; i < 4; i++ {
      _, err := s.Read(onebyte)
      if err == nil {
        fmt.Printf("%s",onebyte)
      }
    }

    if count == Limit-1 {
      count = 0
      time.Sleep(4 * time.Second)
    }

  }
  fmt.Println("Unexpected infite loop exit.")
}
