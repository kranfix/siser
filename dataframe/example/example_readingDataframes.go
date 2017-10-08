package main

import (
  "fmt"
  sdt "github.com/kranfix/siser/dataframe"
)

func main() {
  d := sdt.NewDataframe("OPEN","CHAU")

  msg := [][]byte{
    []byte("OPEXNOPEN01234567899876543210012CHAUOPOPEN3456789987"),
    []byte("654321001234"),
    []byte("5CH"),
    []byte("AUOP"),
    []byte("E"),
    []byte("N01234567899876543210012CHAU"),
  }

  var readed bool
  for i,m := range msg{

    fmt.Printf("MSG %d:\n",i)
    for n,k:= 0,0; n < len(m); n += k {
      k,readed = d.Detect(m[n:])
      if readed {
        fmt.Println("  Completed")
        fmt.Printf("    %s\n",d.Bytes())
        d.CleanBytes()
        fmt.Println("    Cleaning buffer")
      } else {
        fmt.Printf("  Pending message: %d bytes.\n",len(m)-n+1)
      }
      fmt.Printf("    %s\n",d.Bytes())
    }
  }
}
