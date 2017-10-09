package dataframe

type Dataframe struct {
  Core
  init  []byte
  bytes []byte
  end   []byte
  size int
  index int
  state readingState
}

func NewDataframe(init, end string) Dataframe {
  d := Dataframe{}
  n := d.Core.Size()
  d.init = []byte(init)
  d.bytes = make([]byte,n)
  d.end = []byte(end)
  d.size = len(d.init) + n + len(d.end)
  d.index = 0
  d.state = ReadingInit
  return d
}

func (d Dataframe) String() string{
  return d.Core.String()
}

func (d Dataframe) Size() int{
  return d.size
}

func (d *Dataframe) Bytes() []byte {
  return d.bytes
}

func (d *Dataframe) CleanBytes(c byte) {
  for i:= range d.bytes {
    d.bytes[i] = c
  }
}
