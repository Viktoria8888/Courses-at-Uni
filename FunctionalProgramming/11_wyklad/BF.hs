{-# LANGUAGE GeneralizedNewtypeDeriving #-}
import System.IO
import System.Environment
import Control.Monad.Trans.Class
import Control.Monad.Trans.State.Lazy
import Control.Monad.Trans.Identity

data BF
  = MoveL
  | MoveR
  | Inc
  | Dec
  | Input
  | Output
  | While [BF]
  deriving Show

class Monad m => InputMonad m where
  input :: m (Maybe Char)

class Monad m => OutputMonad m where
  output :: Char -> m ()

class Monad m => TapeMonad m where
  moveL :: m ()
  moveR :: m ()
  tapeGet :: m Integer
  tapePut :: Integer -> m ()

instance InputMonad IO where
  input = do
    eof <- isEOF
    if eof then return Nothing
    else fmap Just getChar

instance OutputMonad IO where
  output c = putChar c >> hFlush stdout

newtype StringInputT m a = StringInput (StateT String m a)
  deriving (Functor, Applicative, Monad)

instance Monad m => InputMonad (StringInputT m) where
  input = StringInput $ do
    xs <- get
    case xs of
      [] -> return Nothing
      (x:ys) -> put ys >> return (Just x)

runStringInput :: Monad m => StringInputT m a -> String -> m a
runStringInput (StringInput m) = evalStateT m

newtype TapeT m a = Tape (StateT ([Integer],[Integer]) m a)
  deriving (Functor, Applicative, Monad)

instance Monad m => TapeMonad (TapeT m) where
  tapeGet = Tape $ (head . snd) <$> get
  tapePut x = Tape $ do
    (l, r) <- get
    put (l, x:tail r)
  moveL = Tape $ do
    (l, r) <- get
    put (tail l, head l:r)
  moveR = Tape $ do
    (l, r) <- get
    put (head r:l, tail r)

runTape :: (Monad m) => TapeT m a -> m a
runTape (Tape m) = evalStateT m ([0,0..],[0,0..])

parseBF :: InputMonad m => m [BF]
parseBF = input >>= decide where
  decide Nothing    = return []
  decide (Just ']') = return []
  decide (Just '<') = fmap (MoveL:) parseBF
  decide (Just '>') = fmap (MoveR:) parseBF
  decide (Just '+') = fmap (Inc:) parseBF
  decide (Just '-') = fmap (Dec:) parseBF
  decide (Just ',') = fmap (Input:) parseBF
  decide (Just '.') = fmap (Output:) parseBF
  decide (Just '[') = do
    bf <- parseBF
    fmap (While bf:) parseBF
  decide (Just _) = parseBF

coerceEnum :: (Enum a, Enum b) => a -> b
coerceEnum = toEnum . fromEnum

coerceInput :: Maybe Char -> Integer
coerceInput Nothing = -1
coerceInput (Just c) = coerceEnum c

evalBF :: (TapeMonad m, InputMonad m, OutputMonad m) => BF -> m ()
evalBF MoveL  = moveL
evalBF MoveR  = moveR
evalBF Inc    = tapeGet >>= tapePut . (+1)
evalBF Dec    = tapeGet >>= tapePut . (+ (-1))
evalBF Input  = input >>= tapePut . coerceInput
evalBF Output = tapeGet >>= output . coerceEnum
evalBF (While cmds) = do
  x <- tapeGet
  if x == 0 then return ()
  else evalBlock cmds >> evalBF (While cmds)

evalBlock ::
  (InputMonad m, OutputMonad m, TapeMonad m) => [BF] -> m ()
evalBlock = mapM_ evalBF

main :: IO ()
main = do
  args <- getArgs
  case args of
    [fname] -> do
      prog <- readFile fname
      runTape $ evalBlock $ runIdentityT $ runStringInput parseBF prog
    otherwise ->
      putStrLn "Usage: ./BF FILE"
