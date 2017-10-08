package dataframe

import (
  "fmt"
  "bytes"
  "encoding/binary"
)

type Dht struct {
  T float32 // temperature
  H float32 // humidity
}

type Gps struct {
  La float32
  Lo float32
}

type Core struct {
  Gasppm uint16
  Rain uint8
  Dht
  Gps
  Lx float32
}

func (d Dht) String() string{
  return fmt.Sprintf("\"dht\":{\"t\":%[1]g,\"h\":%[2]g}",d.T,d.H)
}

func (g Gps) String() string{
  return fmt.Sprintf("\"gps\":{\"la\":%g,\"lo\":%g}",g.La,g.Lo)
}

func (c Core) String() string{
  return fmt.Sprintf("{\"mq2\":%v,\"rain\":%v,%v,%v,\"lx\":%v}",
    c.Gasppm, c.Rain, c.Dht, c.Gps, c.Lx)
}

func (c *Core) Size () int {
  return binary.Size(c)
}

// Parse bytes in little endian
func (c *Core) ParseBytes(b []byte) error {
  buf := bytes.NewBuffer(b[:])
  return binary.Read(buf, binary.LittleEndian, c)
}

func (c *Core) ToBytes() ([]byte, error) {
  buf := new(bytes.Buffer)

  err := binary.Write(buf, binary.LittleEndian, c)
  return buf.Bytes(), err
}
