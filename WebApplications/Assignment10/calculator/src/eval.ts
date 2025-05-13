import { evaluate } from 'mathjs';

export function evalExpr(expression: string): string {
  try {
    return evaluate(expression).toString(); 
  } catch (error) {
    return "Error"; 
  }
}