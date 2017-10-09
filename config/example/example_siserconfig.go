package main

import (
  "fmt"
  "github.com/kranfix/siser/config"
)

func main(){
  jsonconf := siserconfig.ReadJsonConfig("./siserconfig.json")
  fmt.Print("Config readed: ")
  fmt.Printf("%s",jsonconf)

  c := siserconfig.NewConfig(jsonconf)
  fmt.Println("\nStructured configuration:")
  fmt.Println("  serial:")
  fmt.Println("    name:",c.Serial.Name)
  fmt.Println("    baud:",c.Serial.Baud)
  fmt.Printf("  mqtt:\n")
  fmt.Println("    server:",c.Mqtt.Server)
  fmt.Println("    user:",c.Mqtt.User)
  fmt.Println("    pass:",c.Mqtt.Pass)
}
