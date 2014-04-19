import Control.Applicative ((<$>))
import Control.Monad
import Data.Word (Word32)
import Data.Bits (testBit)

main = do
  t <- readLn
  inputs <- map (\l -> let [n,k] = words l in (read n, read k)) <$> replicateM t getLine :: IO [(Int,Int)]
  forM_ (zip [1..t] inputs) $ \(i,(n,k)) ->
    putStrLn $ "Case #" ++ show i ++ ": " ++ if k `mod` 2^n == 2^n-1 then "ON" else "OFF"

