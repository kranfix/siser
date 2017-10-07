package main

import (
  "fmt"
  sdt "github.com/kranfix/siser/dataframe"
)

func main(){
  dht := sdt.Dht{T:23.5,H:51.7}
  gps := sdt.Gps{La:-12.01,Lo:-17.04}
  sCore1 := sdt.Core{750, 16, dht, gps, 50}
  sCore2 := sdt.Core{} // without data

  b, err := sCore1.ToBytes()
  if err != nil {
    fmt.Print("Error writing to bytes: ")
    fmt.Println(err)
    return
  }
  fmt.Printf("% x\n", b)

  err = sCore2.ParseBytes(b)
  if err != nil {
    fmt.Print("Error reading from bytes: ")
    fmt.Println(err)
    return
  }
  fmt.Println(sCore2)
}
