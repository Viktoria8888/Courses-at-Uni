(* open Logic *)
(* ⊢ p → p *)

let f1_1 = imp_i (Var("p")) (by_assumption (Var("p")))


(* ⊢p → q → p *)
let f2_1 =  imp_i (Var "p" ) (imp_i(Var "q") (by_assumption (Var "p")))

let f1 = Node(Var("p"), "→", Node(Var("q"), "→",Var("r"))) 
let f2 = Node(Var("p"), "→", Var("q")) 
let f3 = (Var("p")) 
let f1_thm = by_assumption f1 
let f2_thm = by_assumption f2 
let f3_thm = by_assumption f3 
let eif1 = imp_e f1_thm f3_thm 
let eif2 = imp_e f2_thm f3_thm 
let eif1f2 = imp_e eif1 eif2
let res = imp_i f1 (imp_i f2 (imp_i (Var("p")) eif1f2))

let g = imp_i (Bottom) (bot_e (Var "p") (by_assumption (Bottom)))





