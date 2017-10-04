package main

import (
  "fmt"
  "time"
  "bytes"
  "encoding/binary"
  "../siser"
  "github.com/tarm/serial"
)

func main(){
  sDt := siser.SiserDataframe{}

  c := &serial.Config{
    Name: "/dev/ttyUSB0", //"/dev/ttyUSB0"
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

  //mySiser := siser.Siser{Id:1}
  go func() {
    B := make([]byte, binary.Size(sDt))
    for {
      n, err := s.Read(B)
      buf := bytes.NewBuffer(B[:n])
      fmt.Printf("% x",B[:n])
      err = binary.Read(buf, binary.LittleEndian, &sDt)
      if err == nil {
        fmt.Printf("Rx: %v\n", B[:n])
        fmt.Println(sDt)
      }
    }
  }()

  timeout := time.After(15 * time.Second)
  for {
    select{
    case <-timeout:
      return
    }
  }
}
