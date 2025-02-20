type var = string

type formula =
  | Top
  | Var of var
  | Not of formula
  | And of formula * formula

 (* lookup, jak napotka zmieną po raz pierwszy, to chcemy, żeby zwrocił 2 razy,
  pierwszy raz true drugi raz false
  Co znaczy zwrócić 2 razy?
  Można użyć kontynuację 2 razy 
  Jak lookup napotka zmieną po raz drugi, to chcemy, żeby wartościowanie zostało jakie było*)
module type S = sig
  type ans
 
  val lookup : var -> (bool -> ans) -> ans

  val exists : ((bool -> ans) -> ans) -> bool 
  (*obliczenie wyrażamy, jako funkcję czekającą na kontynacje*)
  val forall : ((bool -> ans) -> ans) -> bool
end

module Env : S = struct
  module VarMap = Map.Make(String)

  type ans = bool VarMap.t -> bool

  let lookup x cont env =
    match VarMap.find_opt x env with
    | Some b -> cont b env
    | None   ->
      cont true  (VarMap.add x true  env) ||
      cont false (VarMap.add x false env)

  (* let exists c = c (fun (b:bool) -> (fun  (_: bool VarMap.t) -> b)) VarMap.empty *)
  let exists c = c (fun b _ -> b) VarMap.empty
  (* fun (b:bool) (_: bool VarMap.t -> bool) -> b,
  czyli to wszystko jest typu bool->ans
  c jest typu obliczenia, czyli (bool -> ans) -> ans,
  więc jak nakarmimy kontynuacją, i potem pustym środowiskiem to dostaniemy
  wartość boolowską.

  *)
  let forall c = not (exists 
                    (fun cont -> 
                    c (fun b -> cont (not b))))
end


module F(Env : S) = struct
  let rec eval f cont =
    match f with
    | Top   -> cont true (*tu zwracamy true*)
    | Var x -> Env.lookup x cont (*zwracamy wartość lookupa, więc *)
    | Not f -> eval f (fun b -> cont (not b)) 
    (*najpierw zewaluować f, z kontynuacją, która, kiedy dostanie wynik, to do kontynuacji z którą przychodzę trzeba przekazać not b*)
    | And(f1, f2) ->
      eval f1 (fun b ->
      if b then eval f2 cont
      else cont false)

  let sat   f = Env.exists (eval f)
  let tauto f = Env.forall (eval f)
end
include F(Env)

(* sat Top ;;
tauto Top ;;
tauto (Var "p") ;;
sat (Var "p") ;;

sat (And(Var "p", Not (Var "p"))) ;;
sat (Not(And(Var "p", Not (Var "p")))) ;;
tauto (Not(And(Var "p", Not (Var "p")))) ;; *)