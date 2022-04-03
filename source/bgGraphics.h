const struct
{
  unsigned char road_stone[32 * 32 * 2 + 1];
  unsigned char road_rainbow[32 * 32 * 2 + 1];
} img_road = {
    "\256s\256s\256s\216s\216s\216s\216s\216s\216s\216s\216smkmkmkmkmkmkmkmkM"
    "kMkMkMkMkMkMkMk\060\204\060\204\060\204\060\204\060\204\256s\256s\256s\216s\216"
    "s\216s\216s\216s\216s\216s\216smkmkmkmkmkmkmkmkMkMkMkMkMkMkMkMk\060\204\060"
    "\204\060\204\060\204\060\204\256s\256s\256s\216s\216s\216s\216s\216s\216s\216"
    "s\216smkmkmkmkmkmkmkmkMkMkMkMkMkMkMkMk\060\204\060\204\060\204\060\204\060\204"
    "\256s\256s\256s\216s\216s\216s\216s\216s\216s\216s\216smkmkmkmkmkmkmkmkM"
    "kMkMkMkMkMkMkMk\060\204\060\204\060\204\060\204\060\204\256s\256s\256s\216s\216"
    "s\216s\216s\216s\216s\216s\216smkmkmkmkmkmkmkmkMkMkMkMkMkMkMkMk\060\204\060"
    "\204\060\204\060\204\060\204\256s\256s\256s\216s\216s\216s\216s\216s\216s\216"
    "s\216smkmkmkmkmkmkmkmkMkMkMkMkMkMkMkMk\060\204\060\204\060\204\060\204\060\204"
    "\256s\256s\256s\216s\216s\216s\216s\216s\216s\216s\216smkmkmkmkmkmkmkmkM"
    "kMkMkMkMkMkMkMk\060\204\060\204\060\204\060\204\060\204mkmkmkmkmkmkmkmkmkmkmk"
    "\262\224\262\224\262\224\262\224\262\224\262\224\262\224\262\224\323\234"
    "\323\234\323\234\323\234\323\234\323\234\323\234\323\234mkmkmkmkmkmkmkmk"
    "mkmkmkmkmkmkmkmk\262\224\262\224\262\224\262\224\262\224\262\224\262\224"
    "\262\224\323\234\323\234\323\234\323\234\323\234\323\234\323\234\323\234"
    "mkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmk\262\224\262\224\262\224\262\224\262\224"
    "\262\224\262\224\262\224\323\234\323\234\323\234\323\234\323\234\323\234"
    "\323\234\323\234mkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmk\262\224\262\224\262\224"
    "\262\224\262\224\262\224\262\224\262\224\323\234\323\234\323\234\323\234"
    "\323\234\323\234\323\234\323\234mkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmk\262\224"
    "\262\224\262\224\262\224\262\224\262\224\262\224\262\224\323\234\323\234"
    "\323\234\323\234\323\234\323\234\323\234\323\234mkmkmkmkmkmkmkmkmkmkmkmk"
    "mkmkmkmk\262\224\262\224\262\224\262\224\262\224\262\224\262\224\262\224"
    "\323\234\323\234\323\234\323\234\323\234\323\234\323\234\323\234mkmkmkmk"
    "mkmkmkmkmkmkmkmkmkmkmkmk\262\224\262\224\262\224\262\224\262\224\262\224"
    "\262\224\262\224\323\234\323\234\323\234\323\234\323\234\323\234\323\234"
    "\323\234mkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmk\262\224\262\224\262\224\262\224"
    "\262\224\262\224\262\224\262\224\323\234\323\234\323\234\323\234\323\234"
    "\323\234\323\234\323\234mkmkmkmkmk\060\204\060\204\060\204\216s\216s\216s\216"
    "s\216s\216s\216s\216s\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357"
    "{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\060\204\060\204\060\204"
    "\216s\216s\216s\216s\216s\216s\216s\216s\357{\357{\357{\357{\357{\357{\357"
    "{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\060"
    "\204\060\204\060\204\216s\216s\216s\216s\216s\216s\216s\216s\357{\357{\357"
    "{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357"
    "{\357{\357{\357{\060\204\060\204\060\204\216s\216s\216s\216s\216s\216s\216s"
    "\216s\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357"
    "{\357{\357{\357{\357{\357{\357{\357{\060\204\060\204\060\204\216s\216s\216s"
    "\216s\216s\216s\216s\216s\357{\357{\357{\357{\357{\357{\357{\357{\357{\357"
    "{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\060\204\060\204\060"
    "\204\216s\216s\216s\216s\216s\216s\216s\216s\357{\357{\357{\357{\357{\357"
    "{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357"
    "{\060\204\060\204\060\204\216s\216s\216s\216s\216s\216s\216s\216s\357{\357{"
    "\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357"
    "{\357{\357{\357{\357{\060\204\060\204\060\204\216s\216s\216s\216s\216s\216s"
    "\216s\216s\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357{\357"
    "{\357{\357{\357{\357{\357{\357{\357{\357{mkmkmkmkmkmkmkmkmkmkmkmkmkmkmkm"
    "kmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkm"
    "kmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkm"
    "kmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkm"
    "kmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkm"
    "kmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkm"
    "kmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkm"
    "kmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmkmk\262\224\262\224\262\224"
    "\262\224\262\224\262\224\262\224\262\224\262\224\262\224\262\224\323\234"
    "\323\234\323\234\323\234\323\234\323\234\323\234\323\234\020\204\020\204\020"
    "\204\020\204\020\204\020\204\020\204\020\204\216s\216s\216s\216s\216s",
    "\000\000\000\370\000\370\000\370\000\370\000\370\000\370\000\240\000\000\300\373\300\373\300\373"
    "\300\373\300\373\300\373@\302\000\000\300\377\300\377\300\377\300\377\300\377"
    "\300\377\300\275\000\000\300\007\300\007\300\007\300\007\300\007\300\007@\005\000\000\000\370\000\370"
    "\000\370\000\370\000\370\000\370\000\240\000\000\300\373\300\373\300\373\300\373\300\373"
    "\300\373@\302\000\000\300\377\300\377\300\377\300\377\300\377\300\377\300\275"
    "\000\000\300\007\300\007\300\007\300\007\300\007\300\007@\005\000\000\000\370\000\370\000\370\000\370\000"
    "\370\000\370\000\240\000\000\300\373\300\373\300\373\300\373\300\373\300\373@\302"
    "\000\000\300\377\300\377\300\377\300\377\300\377\300\377\300\275\000\000\300\007\300"
    "\007\300\007\300\007\300\007\300\007@\005\000\000\000\370\000\370\000\370\000\370\000\370\000\370\000\240"
    "\000\000\300\373\300\373\300\373\300\373\300\373\300\373@\302\000\000\300\377\300"
    "\377\300\377\300\377\300\377\300\377\300\275\000\000\300\007\300\007\300\007\300\007"
    "\300\007\300\007@\005\000\000\000\370\000\370\000\370\000\370\000\370\000\370\000\240\000\000\300\373"
    "\300\373\300\373\300\373\300\373\300\373@\302\000\000\300\377\300\377\300\377"
    "\300\377\300\377\300\377\300\275\000\000\300\007\300\007\300\007\300\007\300\007\300\007"
    "@\005\000\000\000\370\000\370\000\370\000\370\000\370\000\370\000\240\000\000\300\373\300\373\300"
    "\373\300\373\300\373\300\373@\302\000\000\300\377\300\377\300\377\300\377\300"
    "\377\300\377\300\275\000\000\300\007\300\007\300\007\300\007\300\007\300\007@\005\000\000\000\240"
    "\000\240\000\240\000\240\000\240\000\240\000\240\000\000@\302@\302@\302@\302@\302@\302@\302"
    "\000\000\300\275\300\275\300\275\300\275\300\275\300\275\300\275\000\000@\005@\005@\005"
    "@\005@\005@\005@\005\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
    "\000\370\000\370\000\370\000\370\000\370\000\370\000\240\000\000\300\373\300\373\300\373\300"
    "\373\300\373\300\373@\302\000\000\300\377\300\377\300\377\300\377\300\377\300"
    "\377\300\275\000\000\300\007\300\007\300\007\300\007\300\007\300\007@\005\000\000\000\370\000\370\000"
    "\370\000\370\000\370\000\370\000\240\000\000\300\373\300\373\300\373\300\373\300\373"
    "\300\373@\302\000\000\300\377\300\377\300\377\300\377\300\377\300\377\300\275"
    "\000\000\300\007\300\007\300\007\300\007\300\007\300\007@\005\000\000\000\370\000\370\000\370\000\370\000"
    "\370\000\370\000\240\000\000\300\373\300\373\300\373\300\373\300\373\300\373@\302"
    "\000\000\300\377\300\377\300\377\300\377\300\377\300\377\300\275\000\000\300\007\300"
    "\007\300\007\300\007\300\007\300\007@\005\000\000\000\370\000\370\000\370\000\370\000\370\000\370\000\240"
    "\000\000\300\373\300\373\300\373\300\373\300\373\300\373@\302\000\000\300\377\300"
    "\377\300\377\300\377\300\377\300\377\300\275\000\000\300\007\300\007\300\007\300\007"
    "\300\007\300\007@\005\000\000\000\370\000\370\000\370\000\370\000\370\000\370\000\240\000\000\300\373"
    "\300\373\300\373\300\373\300\373\300\373@\302\000\000\300\377\300\377\300\377"
    "\300\377\300\377\300\377\300\275\000\000\300\007\300\007\300\007\300\007\300\007\300\007"
    "@\005\000\000\000\370\000\370\000\370\000\370\000\370\000\370\000\240\000\000\300\373\300\373\300"
    "\373\300\373\300\373\300\373@\302\000\000\300\377\300\377\300\377\300\377\300"
    "\377\300\377\300\275\000\000\300\007\300\007\300\007\300\007\300\007\300\007@\005\000\000\000\240"
    "\000\240\000\240\000\240\000\240\000\240\000\240\000\000@\302@\302@\302@\302@\302@\302@\302"
    "\000\000\300\275\300\275\300\275\300\275\300\275\300\275\300\275\000\000@\005@\005@\005"
    "@\005@\005@\005@\005\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
    "\000\370\000\370\000\370\000\370\000\370\000\370\000\240\000\000\300\373\300\373\300\373\300"
    "\373\300\373\300\373@\302\000\000\300\377\300\377\300\377\300\377\300\377\300"
    "\377\300\275\000\000\300\007\300\007\300\007\300\007\300\007\300\007@\005\000\000\000\370\000\370\000"
    "\370\000\370\000\370\000\370\000\240\000\000\300\373\300\373\300\373\300\373\300\373"
    "\300\373@\302\000\000\300\377\300\377\300\377\300\377\300\377\300\377\300\275"
    "\000\000\300\007\300\007\300\007\300\007\300\007\300\007@\005\000\000\000\370\000\370\000\370\000\370\000"
    "\370\000\370\000\240\000\000\300\373\300\373\300\373\300\373\300\373\300\373@\302"
    "\000\000\300\377\300\377\300\377\300\377\300\377\300\377\300\275\000\000\300\007\300"
    "\007\300\007\300\007\300\007\300\007@\005\000\000\000\370\000\370\000\370\000\370\000\370\000\370\000\240"
    "\000\000\300\373\300\373\300\373\300\373\300\373\300\373@\302\000\000\300\377\300"
    "\377\300\377\300\377\300\377\300\377\300\275\000\000\300\007\300\007\300\007\300\007"
    "\300\007\300\007@\005\000\000\000\370\000\370\000\370\000\370\000\370\000\370\000\240\000\000\300\373"
    "\300\373\300\373\300\373\300\373\300\373@\302\000\000\300\377\300\377\300\377"
    "\300\377\300\377\300\377\300\275\000\000\300\007\300\007\300\007\300\007\300\007\300\007"
    "@\005\000\000\000\370\000\370\000\370\000\370\000\370\000\370\000\240\000\000\300\373\300\373\300"
    "\373\300\373\300\373\300\373@\302\000\000\300\377\300\377\300\377\300\377\300"
    "\377\300\377\300\275\000\000\300\007\300\007\300\007\300\007\300\007\300\007@\005\000\000\000\240"
    "\000\240\000\240\000\240\000\240\000\240\000\240\000\000@\302@\302@\302@\302@\302@\302@\302"
    "\000\000\300\275\300\275\300\275\300\275\300\275\300\275\300\275\000\000@\005@\005@\005"
    "@\005@\005@\005@\005\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
    "\000\370\000\370\000\370\000\370\000\370\000\370\000\240\000\000\300\373\300\373\300\373\300"
    "\373\300\373\300\373@\302\000\000\300\377\300\377\300\377\300\377\300\377\300"
    "\377\300\275\000\000\300\007\300\007\300\007\300\007\300\007\300\007@\005\000\000\000\370\000\370\000"
    "\370\000\370\000\370\000\370\000\240\000\000\300\373\300\373\300\373\300\373\300\373"
    "\300\373@\302\000\000\300\377\300\377\300\377\300\377\300\377\300\377\300\275"
    "\000\000\300\007\300\007\300\007\300\007\300\007\300\007@\005\000\000\000\370\000\370\000\370\000\370\000"
    "\370\000\370\000\240\000\000\300\373\300\373\300\373\300\373\300\373\300\373@\302"
    "\000\000\300\377\300\377\300\377\300\377\300\377\300\377\300\275\000\000\300\007\300"
    "\007\300\007\300\007\300\007\300\007@\005\000\000\000\370\000\370\000\370\000\370\000\370\000\370\000\240"
    "\000\000\300\373\300\373\300\373\300\373\300\373\300\373@\302\000\000\300\377\300"
    "\377\300\377\300\377\300\377\300\377\300\275\000\000\300\007\300\007\300\007\300\007"
    "\300\007\300\007@\005\000\000\000\370\000\370\000\370\000\370\000\370\000\370\000\240\000\000\300\373"
    "\300\373\300\373\300\373\300\373\300\373@\302\000\000\300\377\300\377\300\377"
    "\300\377\300\377\300\377\300\275\000\000\300\007\300\007\300\007\300\007\300\007\300\007"
    "@\005\000\000\000\370\000\370\000\370\000\370\000\370\000\370\000\240\000\000\300\373\300\373\300"
    "\373\300\373\300\373\300\373@\302\000\000\300\377\300\377\300\377\300\377\300"
    "\377\300\377\300\275\000\000\300\007\300\007\300\007\300\007\300\007\300\007@\005\000\000\000\240"
    "\000\240\000\240\000\240\000\240\000\240\000\240\000\000@\302@\302@\302@\302@\302@\302@\302"
    "\000\000\300\275\300\275\300\275\300\275\300\275\300\275\300\275\000\000@\005@\005@\005"
    "@\005@\005@\005@\005\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
};

const struct
{
  unsigned char lightgrass_data[32 * 32 * 2 + 1];
  unsigned char darkgrass_data[32 * 32 * 2 + 1];
  unsigned char water_data[32 * 32 * 2 + 1];
  unsigned char lava_data[32 * 32 * 2 + 1];
} img_bg = {
    "Gege)D\311;\010]geGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeg"
    "e)D\312\063\010]geGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGegeGeGeGeGeGeGeGeGeGeGe"
    "(]\010]GeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeiL\011D(]geGeGeGeGeGeGeGeGegege"
    "GeGeGegeGeGeGeGeGeGeGeGeGeGeGeGeGege\011D\252\063\010]geGeGeGeGeGeGeGeGeGeG"
    "eGeGeiL\011D(]geGeGeGeGeGeGeGeGeGeGeGeGe(]\010]GeGeGeGeGeGeGeGeGeGeGeGeGeg"
    "e\011D\252\063\010]geGeGeGegeGeGeGeGeGeGeGeGegegeGeGeGeGeGeGeGeGeGeGeGeGeGe"
    "Ge(]\010]ID\011D(]geiL\011D(]geGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGegeGeGe"
    "gege)D\312\063\010]ge\011D\252\063\010]geGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGe"
    "iL\011D(]geID)D*\063\312\062\351;)D\350T\010]GeGeGeGeGeGeGeGeGeGeGeGeGeGeGeG"
    "eGeGeGege\011D\252\063\010]ge)D\312;\352\062\212*\252\063\351;(]\207eGeGeGeGe"
    "GeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGe(]\010]ID)D*\063\352\062\312*\252*\352\062\352"
    "\062\351;)D)D)D(]geGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGegege\011D\312\063\312*\212"
    "*\252*\252*\252*\212*\212\063\311;\311;\312\063\010]geGeGeGeGeGeGeGeGeGeGeG"
    "eGeGeGeGeGeGeGe(]\010]\350\\\310\\\310\\\310\\\310\\\310\\\010]\010]\010]\010"
    "]GeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGegegegegegegegegegegegegeGeGeGeG"
    "eGeGeGeGeGeGeGeGeGegeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeG"
    "eGeGeGeGeiL\011D(]geGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeG"
    "ege\011D\252\063\010]geGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGe"
    "GeGe(]\010]GeGeGeGeGeGeGeGeGeGeGeGeGegeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGege"
    "geGeGeGeGeGeGeGeGeGeGeGeGeiL\011D(]geGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGe"
    "gegeGeGeGeGeGeGeGege\011D\252\063\010]geGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeG"
    "e)D)D(]geGeGeGeGeGeGe(]\010]GeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGe\311;"
    "\312\063\010]geGeGeGeGeGeGegegeGeGeGeGeGeGeGeGeGegeGeGeGeGeGegeGeGeGeGe\010"
    "]\010]GeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeiL\011D(]geGeGeiL\011D(]geID\011Dg"
    "egeGeGeGegeGeGeGeGeGeGeGeGeGeGeGeGeGege\011D\252\063\010]geGege\011D\252\063\010"
    "]ge)D\312\063)D)D\010]geiL\011D(]geGeGeGeGeGeGeGeGeGeGeGeGe(]\010]GeGeGeGe(]"
    "\010]ID)D*\063\352\062\351;\311;\010]ge\011D\252\063\010]geGeGeGeGeGeGeGeGeGeGe"
    "GeGegegeGeGeGeGegege)D\312;\352\062\212*\352\062\352\062\351;)D\350T(]GeGeG"
    "eGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeiL\011D)D)D*\063\352\062\312*\252*\212*\212*"
    "\212\063\312;\010]geGeGeGeGeGeGeGegeGeGeGeGeGeGeGeGeGege\011D\312\063\311;\311"
    ";\312*\212*\252*\252*\350\\\310\\\010]\010]GeGeGeGeGeGeGeGeiL\011D(]geGeGeG"
    "eGeGeGeGeGe(]\010]\010]\010]\350\\\310\\\310\\\310\\gegegegeGeGeGeGeGeGeGeg"
    "e\011D\252\063\010]geGeGeGeGeGeGeGeGegegegegegegegegeGeGeGeGeGeGeGeGeGeGeGe"
    "Ge(]\010]GeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGegege"
    "GeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGeGe",
    "\250)\207!i\063\011<\010*\207!\211\063\011<\352\062\252*\252*\252*\252*\252*\252"
    "*\252*\251;\351;\352\062\252*\252*\252*\251;\011<\010*\207!\211\063\011<\352\062"
    "\252*\252*\252*\250)\207!\211\063\011<\010*g!\211\063\011<\352\062\252*\252*\252"
    "*\252*\252*\252*\252*\251;\011<\352\062\252*\252*\252*\251;\011<\010*g!\211\063"
    "\011<\352\062\252*\252*\252*\250)\247!\251*\352\062i\063\211;H*\350)\212*\252"
    "*j\063\251;\352\062\252*\010*\310)\251*\352\062\212\063\311;(*\310)\311*\352\062"
    "i\063\211\063\012\063\352\062\212\063\251;\352\062\252*\247!\207!i*\252*\252;\011"
    "<\350)g!\211*\312*\251;\011<\352\062\252*\310)\207!\211*\252*\251;\011<\010*"
    "g!\211*\252*\252;\011<\352\062\212*\311;\011<\352\062\252*\211*\211*\252*\252"
    "*\251;\351;\311\062\211*\350)\310)\251*\352\062\212\063\251;\251*\211*\010*\310"
    ")\211\063\011<\311\062i*\010*\310)\211\063\351;\352\062\252*(*\010*\212*\252*\252"
    "*\252*\252*\252*\252;\011<\352\062\252*\310)\207!i*\252*\251;\011<\352\062\252"
    "*\310)\207!\211\063\011<\352\062\252*\310)\207!\211\063\011<\352\062\252*\310)"
    "g!\211*\312*\251;\251;\352\062\252*(*\010*i\063\312;\010*\207!\211*\312*\352"
    "\062\352\062\252*\252*\310)\207!\251*\352\062\211\063\311;\010*\207!\251*\352"
    "\062\211\063\311;\010*\207!\211*\312*\351;\351;\352\062\252*\310)g!\211\063\011"
    "<\010*\207!\211*\312*\252*\252*\252*\252*\310)\207!\212*\252*\251;\011<\010"
    "*g!\212*\252*\251;\011<\010*\207!\211*\312*\351;\351;\352\062\252*\212*\211"
    "*\251;\351;\311\062i*\350)\310)\212*\252*\212\063\251;\251*i*\350)\310)\251"
    "*\352\062i\063\211;(*\250)\211\063\011<\311*i*\350)\310)\351;\351;\352\062\252"
    "*\312*\252*\252;\011<\352\062\252*\310)\207!\211*\252*\251;\011<\352\062\252"
    "*\310)\207!i*\252*\252;\011<\010*g!\211\063\011<\352\062\252*\310)\207!\352\062"
    "\352\062\212\063\251;\352\062\252*(*\010*i\063\312;\251*i*i\063\311;\012\063\312"
    "\062\211\063\311;\010*\207!\211*\252*\251;\351;\010*\207!\251*\352\062\252*\252"
    "*\310)\207!\252*\252*\251;\011<\352\062\252*\310)g!\211;\011<\352\062\252*\311"
    ";\011<\352\062\212*\251;\011<\010*g!\211*\252*\251;\011<\010*g!\212*\252*\252*"
    "\252*\310)\207!\310)\310)\211\063\011<\352\062\252*\350)\207!\251*\352\062\252"
    "*\252*\352\062\352\062\312*\252*\352\062\352\062i\063\211\063\312\062\252*\352\062"
    "\352\062i\063\211;(*\310)I\063\312;\010*\207!\207!\207!i\063\011<\352\062\252*\310"
    ")\207!i*\252*\252*\252*\252*\252*\252*\252*\252*\252*\312;\011<\352\062\252"
    "*\252*\252*\252;\011<\010*g!\211;)<\010*\207!\250)\207!i\063\011<\352\062\252*"
    "\310)\207!\211*\252*j\063\251;\352\062\252*\212\063\311;(*\310)\251*\352\062"
    "\252*\252*\252*\252*\251;\351;\010*\207!\251*\352\062i\063\211\063\250)\207!"
    "\211\063\011<\352\062\252*\310)\207!\211*\312*\251;\011<\352\062\212*\311;\011"
    "<\010*g!i*\252*\252*\252*\252*\252*\251;\011<\010*\207!\211*\252*\252;\011<\250"
    ")\247!\251*\352\062\212\063\251;\251*i*\350)\310)\251*\352\062\212\063\251;\012"
    "\063\352\062\350)\207!\211*\252*j\063\251;\352\062\252*\352\062\352\062\212*\211"
    "*\252*\252*\251;\351;\247!\207!\211*\252*\251;\011<\352\062\252*\310)g!i*\252"
    "*\251;\011<\352\062\252*\310)\207!\211*\312*\251;\011<\352\062\252*\252*\252"
    "*\252*\312*\252*\252*\251;\351;\211*\211*\350)\310)\211\063\011<\352\062\252"
    "*I\063\211;\312\062\252*\251;\351;\352\062\252*\212*\211*\350)\310)\251*\352"
    "\062\212\063\311;(*\310)\212*\252*j\063\251;\012\063\352\062\312*\312*\310)\207"
    "!\211\063\011<\352\062\252*\312;\011<\352\062\212*\251;\011<\352\062\252*\312*\312"
    "*\310)\207!i*\252*\251;\011<\010*g!\211*\312*\251;\011<\352\062\212*\252*\252"
    "*\310)\207!\251*\352\062\252*\252*\352\062\352\062\212\063\311;H*\350)i\063\312"
    ";\312\062\252*\310)\207!\211*\252*\251;\351;\311\062i*\350)\310)\211\063\011"
    "<\352\062\252*\252*\252*\310)\207!i*\252*\252*\252*\252*\252*\251;\011<\350"
    ")g!\211\063\011<\352\062\252*\310)\207!\211*\312*\251;\011<\352\062\252*\310)"
    "\207!\211\063\011<\352\062\252*\252*\252*\310)\207!I\063\312;(*\310)\212*\252"
    "*\251;\351;\010*\207!\211\063\011<\352\062\252*\212*\211*\350)\310)\251*\352"
    "\062\211\063\311;\010*\207!\251*\352\062\212\063\251;\252*\252*\310)\207!\211"
    "\063\011<\010*g!\211*\312*\251;\011<\010*g!\211\063\011<\352\062\252*\312*\312*\310"
    ")\207!i*\252*\251;\011<\010*\207!\212*\252*\251;\011<\252*\252*\212*i*\251;"
    "\351;\311\062j*\350)\310)\251*\352\062\211*\211*(*\010*\212*\252*\252*\252*"
    "\310)\207!\211*\312*\352\062\352\062\212*\211*\350)\310)\211\063\351;\252*\252"
    "*\312*\312*\251;\351;\352\062\252*\310)\207!i*\252*\252*\312*\310)g!i*\252"
    "*\252*\252*\310)\207!\211*\252*\252*\252*\252*\312*\310)\207!\211\063\011<"
    "\251;\252;(*\250)\211\063\011<\352\062\252*\350)\207!I\063\312;\312\062\252*\350"
    ")\207!I\063\312;\352\062\252*\212*i*i\063\311;\352\062\252*\252*\252*\310)\207"
    "!\251*\352\062\351;\011<\010*g!\211\063\011<\352\062\252*\310)\207!\211;)<\352"
    "\062\252*\310)\207!\211;)<\352\062\252*\312*\252*\312;\011<\352\062\252*\252"
    "*\252*\310)\207!i*\252*\351;\351;\010*\207!\251*\352\062\212\063\251;\251*i"
    "*(*\010*i\063\312;\251*i*(*\010*i\063\312;\312\062\252*(*\350)i\063\312;\352\062"
    "\252*\212*\211*\252*\252*\351;\351;\010*\207!\212*\252*\251;\011<\352\062\252"
    "*\310)g!\211\063\011<\352\062\252*\310)g!\211\063\011<\352\062\252*\310)g!\211"
    ";)<\352\062\252*\312*\312*\252*\252*\352\062\352\062\211*\211*\350)\310)\211"
    "\063\011<\352\062\252*\350)\207!i\063\011<\352\062\252*\350)\207!i\063\011<\352\062"
    "\252*\212*\211*(*\350)i\063\312;\312\062\252*\010*\310)\252*\252*\252*\312*"
    "\310)\207!i\063\011<\352\062\252*\310)\207!\211\063\011<\352\062\252*\310)\207"
    "!\211\063\011<\352\062\252*\312*\312*\310)g!\211\063\011<\352\062\252*\310)\207"
    "!",
    "~\205~\266~\327~\327~\327~\327~\205|l|l|l~\205~\205~\327~\205|l|l|l|l|l|"
    "l|l~\327~\327~\327~\266~\205|l|l|l|l|l|l|l~\205~\327~\266|l|l|l|l~\327~\327"
    "~\327~\327~\327~\327~\327~\327~\266~\266~\266~\266~\266~\327~\327~\266|l"
    "|l|l|l|l|l|l|l|l|l~\266~\327~\266~\205~\327~\266~\327|l|l~\205~\327~\327"
    "~\327~\266~\205~\205~\205~\205~\205~\327~\327|l|l|l|l|l|l|l|l|l|l|l~\266"
    "~\327~\327~\205~\205|l|l|l|l|l|l~\205~\327~\327~\266~\205|l|l|l~\327|l|l"
    "|l|l|l|l|l|l|l|l|l|l|l~\327~\205|l|l|l|l|l|l|l|l|l~\205~\205~\266~\327~\205"
    "|l~\266~\327|l|l|l|l|l|l|l|l|l|l|l|l|l~\327|l|l|l|l|l|l|l|l|l|l|l|l~\205"
    "~\266~\327~\205~\327~\205|l|l|l|l|l|l|l|l|l|l|l|l|l~\327|l|l|l|l|l|l|l|l"
    "|l|l|l|l|l~\205~\266~\327~\327|l|l|l|l|l|l|l|l|l|l|l|l|l|l~\327~\205|l|l"
    "|l|l|l|l|l|l|l|l|l|l|l~\205~\327~\327|l|l|l|l|l|l|l|l|l|l|l|l|l|l~\327~\266"
    "~\205|l|l|l|l|l|l|l|l|l|l|l|l~\266~\327~\327~\327|l|l|l|l|l|l|l|l|l|l|l|"
    "l~\205~\327~\327~\266~\205|l|l|l~\205~\205|l|l|l~\205~\266~\266~\327~\327"
    "~\327~\327~\327~\205|l|l|l|l|l|l|l|l~\327~\327~\327~\327~\327~\327~\327~"
    "\327~\327~\327~\327~\327~\327~\327~\266~\266~\327~\327~\266~\205~\205~\266"
    "~\205~\327~\327~\327|l|l|l|l|l|l~\327~\266~\266~\266~\266~\266~\327~\327"
    "~\327~\327~\327~\266~\327~\327~\327~\327~\266~\205|l|l|l|l|l~\205~\205~\327"
    "~\327~\266~\205|l~\327~\266~\327~\266~\266~\205|l|l~\205|l|l~\327~\266|l"
    "|l~\205~\266~\205|l|l|l|l|l|l|l|l|l~\205~\327~\327~\327~\327~\327~\327~\327"
    "~\327~\327~\327~\266~\266|l|l|l~\327~\205|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l~"
    "\205~\327~\327~\327~\327~\327~\205~\205~\205~\205~\266~\327~\266|l~\327~"
    "\266|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l~\266~\327~\327~\327~\327|l|l|l|l~"
    "\205~\266~\327~\327~\327|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l~\327~\327"
    "~\327|l|l|l|l|l|l~\205~\266~\327~\327|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|"
    "l|l~\266~\327~\205|l|l|l|l|l|l|l~\266~\327~\327|l|l|l|l|l|l|l|l|l|l|l|l|"
    "l|l|l|l|l|l|l~\266~\327~\205|l|l|l|l|l|l|l~\205~\266~\266|l|l|l|l|l|l|l|"
    "l|l|l|l|l|l|l|l|l|l|l|l~\266~\327~\205|l|l|l|l|l|l|l|l~\205~\266|l|l|l|l"
    "|l|l|l|l|l|l|l|l|l|l|l|l|l|l~\205~\266~\327~\266|l|l|l|l|l|l|l|l~\205~\327"
    "~\205|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l~\266~\327~\266~\266~\266|l|l|l|l|l"
    "|l|l|l~\266~\327~\327|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l~\266~\327~\266~\205~"
    "\205~\266~\266~\266|l|l|l|l|l~\205~\327~\266~\327~\266|l|l|l|l|l|l|l|l|l"
    "|l|l|l|l~\266~\327~\327~\266~\266~\205~\266~\327~\327~\266~\205|l|l~\266"
    "~\327~\266|l~\205~\327~\327~\205|l|l|l|l|l|l|l|l|l|l~\205~\327~\327~\205"
    "~\205~\205~\205~\205~\266~\205~\266~\327~\327~\327~\327~\205|l|l|l~\205~"
    "\205~\327~\205|l|l|l|l|l|l|l~\327~\327~\327~\266~\205|l|l|l|l|l|l|l~\205"
    "~\327~\266|l|l|l|l~\327~\327~\327~\327~\327~\327~\327~\327~\266~\266~\266"
    "~\266~\266~\327~\327~\266|l|l|l|l|l|l|l|l~\327~\327~\266~\205~\205~\266~"
    "\205~\327~\327~\327|l|l|l|l|l|l~\327~\327~\327~\327~\327~\327~\327~\327~"
    "\327~\327~\327~\327~\327~\327~\266~\266~\266~\205|l|l|l|l|l~\205~\205~\327"
    "~\327~\266~\205|l~\327~\266~\327~\266~\266~\266~\266~\266~\327~\327~\327"
    "~\327~\327~\266~\327~\327~\327~\327|l|l|l|l|l|l|l|l|l~\205~\327~\327~\327"
    "~\327~\327~\327~\327~\266~\266~\205|l|l~\205|l|l~\327~\266|l|l~\205~\266"
    "~\205|l|l|l|l|l|l|l|l|l|l~\205~\327~\327~\327~\327~\327~\327~\327~\327~\327"
    "~\266~\266|l|l|l~\327~\205|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l~\266~\327~\327"
    "~\327~\327~\205~\205~\205~\205~\266~\327~\266|l~\327~\266|l|l|l|l|l|l|l|"
    "l|l|l|l|l|l|l|l|l|l|l~\327~\327~\327|l|l|l|l|l~\205~\266~\327~\327~\327|"
    "l|l|l|l|l|l|l",
    "`\373`\373\000\370\000\370\000\370\000\330\000\370\000\370\000\370\000\370\340\377\240\375"
    "`\373`\373`\373`\373`\373`\373\000\370\000\370\000\370\000\330\000\370\000\370\000\370"
    "\000\370\340\377\240\375`\373`\373`\373`\373`\373\000\370\000\370\000\330\000\330\000"
    "\370\000\370`\373\000\370\240\375\000\370`\373\240\375\000\370`\373`\373`\373\000\370"
    "\000\370\000\330\000\330\000\370\000\370`\373\000\370\240\375\000\370`\373\240\375\000\370"
    "`\373`\373`\373\000\370\000\370\000\330\000\260\000\330\000\370`\373`\373`\373\240\375"
    "\240\375\000\370\000\370`\373`\373`\373\000\370\000\370\000\330\000\260\000\330\000\370`"
    "\373`\373`\373\240\375\240\375\000\370\000\370`\373`\373`\373`\373\000\370\000\330"
    "\000\260\000\370\000\370`\373`\373`\373`\373\000\370\000\370\000\370\000\370`\373`\373"
    "`\373\000\370\000\330\000\260\000\370\000\370`\373`\373`\373`\373\000\370\000\370\000\370"
    "\000\370`\373\000\370\000\370\000\370\000\370\000\330\000\370\000\370\000\370`\373`\373\000\370"
    "\000\370\000\370`\373\000\370\000\370\000\370\000\370\000\370\000\370\000\330\000\370\000\370\000"
    "\370`\373`\373\000\370\000\370\000\370`\373\000\370\000\370\000\330\000\330\340\377\240"
    "\375\000\330\000\370\000\330\000\370\000\370`\373\000\370\000\370\000\370`\373`\373\000\370"
    "\000\330\000\330\340\377\240\375\000\330\000\370\000\330\000\370\000\370`\373\000\370\000\370"
    "\000\370`\373`\373\000\370\000\370\240\375\000\330\000\370\240\375\000\370`\373\000\330"
    "\000\370\000\370`\373\000\370\000\370`\373`\373`\373\000\370\240\375\000\330\000\370\240"
    "\375\000\370`\373\000\330\000\370\000\370`\373\000\370\000\370`\373`\373`\373`\373`\373"
    "\240\375\240\375`\373`\373`\373`\373`\373`\373\000\370\000\370`\373`\373`\373"
    "`\373`\373`\373\240\375\240\375`\373`\373`\373`\373`\373`\373\000\370\000\370"
    "`\373`\373`\373`\373`\373`\373\000\370\000\370\000\370\000\370`\373`\373\340\377"
    "\240\375\000\330\000\370`\373`\373`\373`\373`\373`\373\000\370\000\370\000\370\000\370"
    "`\373`\373\340\377\240\375\000\330\000\370`\373`\373`\373`\373`\373\000\370\000\370"
    "\000\370`\373\000\370\000\330\240\375`\373`\373\240\375\000\370\000\370`\373`\373`"
    "\373`\373\000\370\000\370\000\370`\373\000\370\000\330\240\375`\373`\373\240\375\000"
    "\370\000\370`\373`\373`\373`\373\000\370\000\330\000\370`\373`\373\000\330\000\370\240"
    "\375\240\375`\373\000\370\000\330\000\370`\373`\373`\373\000\370\000\330\000\370`\373"
    "`\373\000\330\000\370\240\375\240\375`\373\000\370\000\330\000\370`\373`\373\000\370"
    "\000\370\000\330\000\370`\373`\373`\373\000\370`\373`\373`\373\000\370\000\330\000\370"
    "`\373`\373\000\370\000\370\000\330\000\370`\373`\373`\373\000\370`\373`\373`\373\000"
    "\370\000\330\000\370`\373`\373\000\330\000\330\000\370`\373`\373`\373`\373\000\370\000"
    "\370\000\370\000\370\000\330\000\330\000\370`\373\000\370\000\330\000\330\000\370`\373`\373"
    "`\373`\373\000\370\000\370\000\370\000\370\000\330\000\330\000\370`\373\000\370\240\375\000"
    "\370\000\370\000\370`\373`\373`\373`\373\000\370\000\370\000\370\000\370\000\370\000\370"
    "\000\370\340\377\240\375\000\370\000\370\000\370`\373`\373`\373`\373\000\370\000\370"
    "\000\370\000\370\000\370\000\370\000\370\340\377\000\370\240\375`\373\000\370\000\370`\373"
    "`\373\000\370\000\330\000\370\000\370\000\370`\373`\373\340\377\000\370\000\370\240\375"
    "`\373\000\370\000\370`\373`\373\000\370\000\330\000\370\000\370\000\370`\373`\373\340\377"
    "\000\370\240\375`\373`\373\000\370\000\370\000\370\000\370\000\330\000\330\000\370\000\370"
    "`\373`\373`\373`\373\240\375\240\375`\373`\373\000\370\000\370\000\370\000\370\000"
    "\330\000\330\000\370\000\370`\373`\373`\373`\373\240\375`\373`\373\000\370\000\370"
    "\000\370\000\330\000\370\000\370\000\370\000\370\340\377\240\375`\373`\373`\373`\373"
    "`\373`\373\000\370\000\370\000\370\000\330\000\370\000\370\000\370\000\370\340\377\240\375"
    "`\373`\373`\373`\373`\373\000\370\000\370\000\330\000\330\000\370\000\370`\373\000\370"
    "\240\375\000\370`\373\240\375\000\370`\373`\373`\373\000\370\000\370\000\330\000\330"
    "\000\370\000\370`\373\000\370\240\375\000\370`\373\240\375\000\370`\373`\373`\373\000"
    "\370\000\370\000\330\000\260\000\330\000\370`\373`\373`\373\240\375\240\375\000\370\000"
    "\370`\373`\373`\373\000\370\000\370\000\330\000\260\000\330\000\370`\373`\373`\373\240"
    "\375\240\375\000\370\000\370`\373`\373`\373`\373\000\370\000\330\000\260\000\370\000\370"
    "`\373`\373`\373`\373\000\370\000\370\000\370\000\370`\373`\373`\373\000\370\000\330\000"
    "\260\000\370\000\370`\373`\373`\373`\373\000\370\000\370\000\370\000\370`\373\000\370\000"
    "\370\000\370\000\370\000\330\000\370\000\370\000\370`\373`\373\000\370\000\370\000\370`\373"
    "\000\370\000\370\000\370\000\370\000\370\000\370\000\330\000\370\000\370\000\370`\373`\373\000"
    "\370\000\370\000\370`\373\000\370\000\370\000\330\000\330\340\377\240\375\000\330\000\370"
    "\000\330\000\370\000\370`\373\000\370\000\370\000\370`\373`\373\000\370\000\330\000\330\340"
    "\377\240\375\000\330\000\370\000\330\000\370\000\370`\373\000\370\000\370\000\370`\373`\373"
    "\000\370\000\370\240\375\000\330\000\370\240\375\000\370`\373\000\330\000\370\000\370`\373"
    "\000\370\000\370`\373`\373`\373\000\370\240\375\000\330\000\370\240\375\000\370`\373"
    "\000\330\000\370\000\370`\373\000\370\000\370`\373`\373`\373`\373`\373\240\375\240"
    "\375`\373`\373`\373`\373`\373`\373\000\370\000\370`\373`\373`\373`\373`\373`"
    "\373\240\375\240\375`\373`\373`\373`\373`\373`\373\000\370\000\370`\373`\373"
    "`\373`\373`\373`\373\000\370\000\370\000\370\000\370`\373`\373\340\377\240\375\000"
    "\330\000\370`\373`\373`\373`\373`\373`\373\000\370\000\370\000\370\000\370`\373`\373"
    "\340\377\240\375\000\330\000\370`\373`\373`\373`\373`\373\000\370\000\370\000\370`"
    "\373\000\370\000\330\240\375`\373`\373\240\375\000\370\000\370`\373`\373`\373`\373"
    "\000\370\000\370\000\370`\373\000\370\000\330\240\375`\373`\373\240\375\000\370\000\370"
    "`\373`\373`\373`\373\000\370\000\330\000\370`\373`\373\000\330\000\370\240\375\240"
    "\375`\373\000\370\000\330\000\370`\373`\373`\373\000\370\000\330\000\370`\373`\373\000"
    "\330\000\370\240\375\240\375`\373\000\370\000\330\000\370`\373`\373\000\370\000\370\000"
    "\330\000\370`\373`\373`\373\000\370`\373`\373`\373\000\370\000\330\000\370`\373`\373"
    "\000\370\000\370\000\330\000\370`\373`\373`\373\000\370`\373`\373`\373\000\370\000\330"
    "\000\370`\373`\373\000\330\000\330\000\370`\373`\373`\373`\373\000\370\000\370\000\370"
    "\000\370\000\330\000\330\000\370`\373\000\370\000\330\000\330\000\370`\373`\373`\373`\373"
    "\000\370\000\370\000\370\000\370\000\330\000\330\000\370`\373\000\370\240\375\000\370\000\370"
    "\000\370`\373`\373`\373`\373\000\370\000\370\000\370\000\370\000\370\000\370\000\370\340"
    "\377\240\375\000\370\000\370\000\370`\373`\373`\373`\373\000\370\000\370\000\370\000\370"
    "\000\370\000\370\000\370\340\377\000\370\240\375`\373\000\370\000\370`\373`\373\000\370"
    "\000\330\000\370\000\370\000\370`\373`\373\340\377\000\370\000\370\240\375`\373\000\370"
    "\000\370`\373`\373\000\370\000\330\000\370\000\370\000\370`\373`\373\340\377\000\370\240"
    "\375`\373`\373\000\370\000\370\000\370\000\370\000\330\000\330\000\370\000\370`\373`\373"
    "`\373`\373\240\375\240\375`\373`\373\000\370\000\370\000\370\000\370\000\330\000\330"
    "\000\370\000\370`\373`\373`\373`\373\240\375",
};