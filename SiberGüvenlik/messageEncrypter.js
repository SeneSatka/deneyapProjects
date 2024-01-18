// const text =
//   "NLÜJTLARURĞÇHBHAPUFLEALÇRUAVIVÇRŞFLŞVKTHUHLTLŞÇAVÜRŞZAVNAHUTHUHFLÜLBÜLTLARÜRÜÇLAÜLÇRÜHÜVÇLŞÜVTVSRFLUHTĞLULIRTRURÖHFHİPTPŞFLDĞHGÇLŞÜVTVSRTLARNRIRÇVZTHUVÜIRAIHCTPŞÇHVÇDĞHTÇPHGBEALTREİALÇBRĞLORÇRUTLAHTUHŞÇHKPATHA";
const text = "Bli".toUpperCase();
const alfabe = "ABCÇDEFGĞHIİJKLMNOÖPRSŞTUÜVYZ";
let newText = "";
let i = 1;
for (const letter of text) {
  if (alfabe.indexOf(letter.toUpperCase()) - i < 0) {
    newText += alfabe[alfabe.length - i];
  } else {
    newText += alfabe[alfabe.indexOf(letter) - i];
  }
}

console.log(`${i} : ${newText}\n\n`);
