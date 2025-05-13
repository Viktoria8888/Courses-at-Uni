import './style.css'
import {evalExpr} from './eval.ts'
let calc = document.getElementById("calculator")

if (!calc){
  throw new Error("Calc not found in DOM")
}

calc.addEventListener("click", (event)=>{
  if (event.target instanceof HTMLButtonElement){
    let input = calc.querySelector("input");
    if (!input){
      throw new Error("input is not found in DOM")
    }
    let button = event.target
    let value = button.innerText
    switch (value){
      case "=":
        let result= evalExpr(input.value);
        input.value = result
        break;
      case "DEL":
        input.value = input.value.slice(0,-1);
        break;
      case "CE":
        input.value = "";
        break;
      default:
        input.value += value
    }}
})
