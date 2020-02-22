type props = string;
type scene =
  | COLOR(Color.Rgba.t)
  | HSV
  | CT
  | CF
  | AUTO_DELAY_OFF;

type t =
  | GET_PROP(list(props))
  | SET_CT_ABX({
      ct_value: int,
      effect: string,
      duration: int,
    })
  | SET_RGB({
      rgb_value: int,
      effect: string,
      duration: int,
    })
  | SET_HSV({
      hue: int,
      sat: int,
      effect: string,
      duration: int,
    })
  | SET_BRIGHT({
      brightness: int,
      effect: string,
      duration: int,
    })
  | SET_POWER({
      power: string,
      effect: string,
      duration: int,
      mode: int,
    })
  | TOGGLE
  | SET_DEFAULT
  | START_CF({
      count: int,
      action: int,
      flow_expression: string,
    })
  | STOP_CF
  | SET_SCENE(scene)
  | CRON_ADD({
      type_: int,
      value: int,
    })
  | CRON_GET({type_: int})
  | CRON_DEL({type_: int})
  | SET_ADJUST({
      action: string,
      prop: string,
    })
  | SET_MUSIC({
      action: int,
      host: string,
      port: int,
    })
  | SET_NAME({name: string})
  | BG_SET_RGB({
      rgb_value: int,
      effect: string,
      duration: int,
    })
  | BG_SET_HSV({
      hue: int,
      sat: int,
      effect: string,
      duration: int,
    })
  | BG_SET_CT_ABX({
      ct_value: int,
      effect: string,
      duration: int,
    })
  | BG_START_CF({
      count: int,
      action: int,
      flow_expresion: string,
    })
  | BG_STOP_CF
  | BG_SET_SCENE({
      class_: string,
      val1: int,
      val2: int,
      val3: int,
    })
  | BG_SET_DEFAULT
  | BG_SET_POWER({
      power: string,
      effect: string,
      duration: int,
      mode: int,
    })
  | BG_SET_BRIGHT({
      brightness: int,
      effect: string,
      duration: int,
    })
  | BG_SET_ADJUST({
      action: string,
      prop: string,
    })
  | BG_TOGGLE
  | DEV_TOGGLE
  | ADJUST_BRIGHT({
      percentage: int,
      duration: int,
    })
  | ADJUST_CT({
      percentage: int,
      duration: int,
    })
  | ADJUST_COLOR({
      percentage: int,
      duration: int,
    })
  | BG_ADJUST_BRIGHT({
      percentage: int,
      duration: int,
    })
  | BG_ADJUST_CT({
      percentage: int,
      duration: int,
    })
  | BG_ADJUST_COLOR({
      percentage: int,
      duration: int,
    });

let get_color_rgb = t => Color.Rgba.(t.r lsl 16 + t.g lsl 8 + t.b);
let get_intensity = t => Color.Rgba.(Base.Float.(t.a * 100.0 |> to_int));
let serialize = t => {
  (
    switch (t) {
    | TOGGLE => Ok((`String("toggle"), `List([])))
    | SET_SCENE(COLOR(color)) =>
      Ok((
        `String("set_scene"),
        `List([
          `String("color"),
          `Int(get_color_rgb(color)),
          `Int(get_intensity(color)),
        ]),
      ))
    | _ => Error("Not Implemented")
    }
  )
  |> Base.Result.map(~f=((methodName, params)) =>
       `Assoc([
         ("id", `Int(1)),
         ("method", methodName),
         ("params", params),
       ])
     );
};