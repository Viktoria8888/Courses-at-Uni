open Qbf;;
open QBF;;
is_true (All("p", Var "p"));;
(* - : bool = false *)
let formula =
  All ("p",
    Not (
      All ("q",
        Not (
          And (
            Not (And (Var "p", Var "q")),
            Not (And (Not (Var "p"), Not (Var "q")))
          )
        )
      )
    )
  );;
(* val formula : formula =
  All ("p",
   Not
    (All ("q",
      Not
       (And (Not (And (Var "p", Var "q")),
         Not (And (Not (Var "p"), Not (Var "q")))))))) *)
is_true formula;;
(* - : bool = true *)
(* #utop_stash test_qbf.ml;; *)
(* Error: Syntax error *)
#utop_stash test_qbf;;
(* Directive `utop_stash' expects a `string' literal, got an identifier. *)
