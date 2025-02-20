module PF where

import Control.Monad
import Control.Applicative
import Control.Monad.Trans.Class
import ListT

runListT :: Monad m => ListT m a -> m [a]
runListT (ListT m) = do
  r <- m
  case r of
    Nothing -> return []
    Just (x, m') -> fmap (x:) $ runListT m'

type Triple = (Integer, Integer, Integer)

select :: MonadPlus m => Integer -> Integer -> m Integer
select a b =
  if a >= b then mzero
  else return a `mplus` select (a+1) b

triples :: Integer -> ListT IO ()
triples n = do
  a <- select 1 n
  b <- select a n
  c <- select b n
  guard (a*a + b*b == c*c)
  lift $ print (a, b, c)
