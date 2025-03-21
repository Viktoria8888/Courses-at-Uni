type var = string

type formula =
  | Top
  | Var of var
  | Not of formula
  | And of formula * formula

module type S = sig
  val lookup : var -> bool
  val exists : (unit -> bool) -> bool
  (* czy istnieje takie środowisko dla którego funkcja unit->bool zwróci true *)
  val forall : (unit -> bool) -> bool
  (* czy dla wszystkich środowisk funkcja unit->bool zwróci true *)
end

module F(Env : S) = struct
  let rec eval f =
    match f with
    | Top   -> true
    | Var x -> Env.lookup x
    | Not f -> not (eval f)
    | And(f1, f2) -> eval f1 && eval f2

  let sat   f = Env.exists (fun () -> eval f)
  let tauto f = Env.forall (fun () -> eval f)
end
