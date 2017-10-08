package main

import (
  "fmt"
  sdt "github.com/kranfix/siser/dataframe"
)

func main(){
  dht := sdt.Dht{T:23.5,H:51.0}
  gps := sdt.Gps{La:-12.0966515,Lo:-77.03060644}
  sCore1 := sdt.Core{1000, 15, dht, gps, 55}
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
