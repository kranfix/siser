package siserconfig

import (
  "fmt"
  "os"
  "encoding/json"
  "io/ioutil"
  "github.com/tarm/serial"
)

type Config struct {
  Serial serial.Config
  Mqtt Mqtt
}

type Mqtt struct {
  Server string
  User string
  Pass string
}


func ReadJsonConfig(filepath string) []byte {
  json, e := ioutil.ReadFile(filepath)
  if e != nil {
    fmt.Printf("File error: %v\n", e)
    fmt.Println("Generate a configuration file siserconfig.json")

    fmt.Println("Example:")
    fmt.Println("{")
    fmt.Println("  \"serial\":\"/dev/ttyUSB0\"")
    fmt.Println("  \"mqtt\":{")
    fmt.Println("    \"server\":\"tcp://myserver.com:1883\",")
    fmt.Println("    \"user\":\"myUsername\",")
    fmt.Println("    \"pass\":\"myPassword\",")
    fmt.Println("  }")
    fmt.Println("}")

    os.Exit(1)
  }

  return json
}

func NewConfig(jsonconf []byte) (c *Config) {
  c = new(Config)
  err := json.Unmarshal(jsonconf, c)
  if err != nil {
		fmt.Println("error:", err)
	}
  return
}
