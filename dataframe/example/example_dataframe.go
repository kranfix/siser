package main

import (
  sdt "github.com/kranfix/siser/dataframe"
)

func main(){
  dht := sdt.Dht{T:23.5,H:51.7}
  fmt.Println(dht)

  gps := sdt.Gps{La:-22.01,H:-17.04}
  fmt.Println(gps)

  sDt := sdt.Dataframe{750, 16, dht, gps, 50}
  fmt.Println(sDt)
}
