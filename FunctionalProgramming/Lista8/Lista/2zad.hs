data StreamTrans i o a
    = Return a
    | ReadS (Maybe i -> StreamTrans i o a)
    | WriteS o (StreamTrans i o a)

next :: Maybe Char -> StreamTrans Char Char ()
next Nothing = Return ()
next (Just x) = WriteS ()
toLower :: StreamTrans Char Char ()
toLower = do
    ReadS 
    WriteS
    toLower
        