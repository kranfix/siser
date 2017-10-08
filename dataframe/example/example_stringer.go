package main

import (
  "fmt"
  sdt "github.com/kranfix/siser/dataframe"
)

func main(){
  dht := sdt.Dht{T:23.5,H:51.7}
  fmt.Println(dht)

  gps := sdt.Gps{La:-22.01,Lo:-17.04}
  fmt.Println(gps)

  sCore := sdt.Core{750, 16, dht, gps, 50}
  fmt.Println(sCore)

  sDataframe := sdt.NewDataframe("HOLA","CHAU")
  sDataframe.Core = sCore
  fmt.Println(sDataframe)
}
