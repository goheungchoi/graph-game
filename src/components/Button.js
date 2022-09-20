import { useState, useEffect } from "react";

function Button({style}) {
  const [percentage, setPercentage] = useState(0.0);
  const [popularity, setPopularity] = useState(0.0);
  useEffect(() => {
    if (pop !== undefined) {
      if (pop <= 150.0) {
        setPercentage((pop / 150.0 * 100.0).toFixed(1));
      } else {
        setPercentage(100.0);
      }
      setPopularity(pop.toFixed(1));
    }
  }, [] )
  return (
    <div
      style={style}
    >
      {text}
    </div>
  );
}

export default Popularity;