
type formula = 
 |Bottom
 |Var of string
 |Node of formula * string * formula

let rec string_of_formula f = match f with
  | Bottom -> "⊥"
  | (Var v) -> v
  | Node(l, o, r) -> let ls = (string_of_formula l) and rs = (string_of_formula r) in
    begin match l with 
      |Node(_, _, _) -> "(" ^ ls ^ ")"^ o ^ rs
      |_ -> ls ^ o ^ rs
    end 
  
(* let f1 = Node (Var "p", "→", Var "q");; *)
(* let f2 =Node( Node(Var "p", "→", Bottom), "→",Node(Var "p", "→", Var "q"));; *)
let pp_print_formula fmtr f =
  Format.pp_print_string fmtr (string_of_formula f)

type theorem  = formula list * formula

let assumptions thm = (fst thm)

let consequence thm = (snd thm)

let pp_print_theorem fmtr thm =
  let open Format in
  pp_open_hvbox fmtr 2;
  begin match assumptions thm with
  | [] -> ()
  | f :: fs ->
    pp_print_formula fmtr f;
    fs |> List.iter (fun f ->
      pp_print_string fmtr ",";
      pp_print_space fmtr ();
      pp_print_formula fmtr f);
    pp_print_space fmtr ()
  end;
  pp_open_hbox fmtr ();
  pp_print_string fmtr "⊢";
  pp_print_space fmtr ();
  pp_print_formula fmtr (consequence thm);
  pp_close_box fmtr ();
  pp_close_box fmtr ()

let by_assumption f = ([f], f)

let imp_i f thm = 
  let new_assumptions = List.filter (fun x-> x!=f) (assumptions thm) in
    (new_assumptions, Node(f, " → ", consequence(thm)))

let imp_e th1 th2 =
  let new_assumptions = (assumptions th1) @ (assumptions th2) in
  match consequence th1 with
  | Node (_, _, rs) -> (new_assumptions, rs)
  | f -> (new_assumptions, f)  

let bot_e f thm = (assumptions thm, f)

(* TESTS *)

(* let formula1 = Node (Var "p", "→", Var "p")

let formula2 = Node (Var "p", "→", Node (Var "q", "→", Var "p"))

let formula3 = Node (
  Node (Node (Var "p", "→", Node (Var "q", "→", Var "r")), "→", Node (Var "p", "→", Var "q")),
  "→",
  Node (Var "p", "→", Var "r")
)

let formula4 = Node (Bottom, "→", Var "p")


let () =
  Format.printf "Formula 1: %a\n" pp_print_formula formula1;
  Format.printf "Formula 2: %a\n" pp_print_formula formula2;
  Format.printf "Formula 3: %a\n" pp_print_formula formula3;
  Format.printf "Formula 4: %a\n" pp_print_formula formula4; *)


