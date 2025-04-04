type var = string

type formula =
  | Top
  | Var of var
  | Neg of formula
  | And of formula * formula

module type S = sig
  type ans

  type 'a t

  val return : 'a -> 'a t
  val bind   : 'a t -> ('a -> 'b t) -> 'b t

  val lookup : var -> bool t

  val exists : bool t -> bool
  val forall : bool t -> bool
end

module F(Env : S) = struct
  open Env

  let rec eval f =
    match f with
    | Top   -> return true
    | Var x -> lookup x
    | Neg f ->
      bind (eval f) (fun b -> return (not b))
    | And(f1, f2) ->
      bind (eval f1) (fun b ->
      if b then eval f2
      else return false)

  let sat   f = Env.exists (eval f)
  let tauto f = Env.forall (eval f)
end

module Env = struct
  module VarMap = Map.Make(String)

  type ans = bool VarMap.t -> bool

  type 'a t = ('a -> ans) -> ans

  let return x cont = cont x
  let bind m f cont = m (fun x -> f x cont)

  let lookup x (cont : bool -> ans) : ans =
    fun (env : bool VarMap.t) ->
    match VarMap.find_opt x env with
    | Some v -> cont v env
    | None   ->
      cont true (VarMap.add x true env) ||
      cont false (VarMap.add x false env)

  let exists c = c (fun b _ -> b) VarMap.empty
  let forall c = not (exists (fun cont -> (c (fun b -> cont (not b)))))
end

include F(Env)
