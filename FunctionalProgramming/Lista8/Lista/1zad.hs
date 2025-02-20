import Data.Char 
import GHC.IO.Handle (isEOF)
echoLower :: IO ()
echoLower = do
    eof <- isEOF
    if eof then 
        return ()
    else do
        c <- getChar
        putChar $ toLower c
        putChar '\n'
        echoLower


main :: IO ()
main = echoLower