package siser

import "fmt"

type Dht struct {
  T float32 // temperature
  H float32 // humidity
}

type Gps struct {
  La float32
  Lo float32
}

type SiserDataframe struct {
  Gasppm uint16
  Rain uint8
  Dht
  Gps
  Lx float32
}

type Siser struct {
  Id uint32
  SiserDataframe
}

func (d Dht) String() string{
  return fmt.Sprintf("\"dht\":{\"t\":%[1]g,\"h\":%[2]g}",d.T,d.H)
}

func (g Gps) String() string{
  return fmt.Sprintf("\"gps\":{\"la\":%g,\"lo\":%g}",g.La,g.Lo)
}

func (s SiserDataframe) String() string{
  return fmt.Sprintf("{\"mq2\":%v,\"rain\":%v,%v,%v,\"lx\":%v}",
    s.Gasppm, s.Rain, s.Dht, s.Gps, s.Lx)
}
