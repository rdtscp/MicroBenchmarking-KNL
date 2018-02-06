let freq = 1300000000;

let arg3 = process.argv[2];

let cycles = arg3;
let secs = cycles/freq;
console.log(cycles + " Cycles\t@ 2.4GHz\t= " + (secs*1000000000).toFixed(2) + "ns");
let ns = arg3;
secs = ns / 1000000000;
console.log(ns + " Nano(s)\t@ 2.4GHz\t= " + (secs * freq).toFixed(2) + " Cycles");