package dataframe

type Dataframe struct {
  Core
  Init []byte
  End []byte
}

func NewDataframe(init, end string) Dataframe {
  d := Dataframe{}
  d.Init = []byte(init)
  d.End = []byte(end)
  return d
}

func (t Dataframe) String() string{
  return t.Core.String()
}
