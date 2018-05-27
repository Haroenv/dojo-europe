open SimpleMaps;
/* why do you need to do this? */
open Belt;

type state = {locations: array(Fetcher.data)};

type action =
  | LocationsReceived(array(Fetcher.data));

let make = _children => {
  /* I just wanted setState */
  ...ReasonReact.reducerComponent("DojoMap"),
  didMount: self =>
    Fetcher.fetchGet(
      /* I expect one more indentation here */
      ~url="https://immense-river-25513.herokuapp.com/locations", ~cb=data =>
      self.send(LocationsReceived(data))
    ),
  reducer: (action, _state) =>
    switch (action) {
    /* why is this not indented? */
    | LocationsReceived(locations) =>
      ReasonReact.Update({locations: locations})
    },
  initialState: () => {locations: [||]},
  render: self =>
    <div>
      <ComposableMap>
        <ZoomableGroup>
          <Geographies geography="/world-50m.json">
            ...(
                 (geographies, projection) =>
                   Array.map(geographies, geography =>
                     <Geography
                       key=(Geography.id(geography))
                       geography
                       projection
                       fill="white"
                       stroke="black"
                     />
                   )
               )
          </Geographies>
          <Markers>
            ...(
                 Array.map(self.state.locations, data =>
                   <DataMarker data>
                     <circle r="3" fill="red" />
                     <text fill="red">
                       (ReasonReact.string(Fetcher.username(data)))
                     </text>
                   </DataMarker>
                 )
               )
          </Markers>
        </ZoomableGroup>
      </ComposableMap>
    </div>,
  /* why does comment get moved */
};
