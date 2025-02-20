module Triples where

import Control.Monad
import Control.Applicative

type Triple = (Integer,Integer,Integer)

select :: MonadPlus m => [a] -> m a
select = foldr (mplus . return) mzero

triples :: MonadPlus m => Integer -> m Triple
triples n = do
  a <- select [1..n]
  b <- select [a..n]
  c <- select [b..n]
  guard (a*a + b*b == c*c)
  return (a,b,c)

data BT a
  = Return a
  | MZero
  | MPlus (BT a) (BT a)
  deriving (Show)

instance Functor BT where
  fmap f m = m >>= return . f

instance Applicative BT where
  pure  = Return
  (<*>) = ap

instance Monad BT where
  Return x    >>= f = f x
  MZero       >>= f = MZero
  MPlus m1 m2 >>= f = MPlus (m1 >>= f) (m2 >>= f)

instance Alternative BT where
  empty = MZero
  (<|>) = MPlus

instance MonadPlus BT where

runBT :: MonadPlus m => BT a -> m a
runBT (Return x)    = return x
runBT MZero         = mzero
runBT (MPlus m1 m2) = mplus (runBT m1) (runBT m2)
