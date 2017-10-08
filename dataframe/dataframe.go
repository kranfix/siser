package dataframe

type readingState byte

const (
  ReadingInit readingState = iota
  ReadingCore
  ReadingEnd
)

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

func (d *Dataframe) Detect(b []byte) (i int, readed bool) {
  n := len(b)
  readed = false
  for i = 0; i < n; i++ {
    switch d.state {
    case ReadingCore:
      N := copy(d.bytes[d.index:],b[i:])
      d.index += N
      i += N
      if d.index == cap(d.bytes) {
        d.index = 0
        d.state = ReadingEnd
        d.Core.ParseBytes(d.bytes)
        readed = true
        return
      }
    /*case ReadingEnd:
      if b[i] == d.init[d.index] {
        d.index++
      }
      b[i] == 0; // cleaning buffer

      if d.index == len(d.init) {
        d.index = 0
        d.state = ReadingInit
      }*/
    default:
      if b[i] == d.init[0] {
        d.index = 1
      } else if b[i] != d.init[d.index] {
        d.index = 0
      } else {
        d.index++
      }

      if d.index == len(d.init) {
        d.index = 0
        d.state = ReadingCore
      }
    }
  }
  return
}
