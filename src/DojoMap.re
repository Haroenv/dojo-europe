open SimpleMaps;
open Belt;

type state = {locations: array(Fetcher.data)};

type action =
  | LocationsReceived(array(Fetcher.data));

let initialState = () => {locations: [||]};

let reducer = (action, _state) =>
  switch (action) {
  | LocationsReceived(locations) =>
    ReasonReact.Update({locations: locations})
  };

let component = ReasonReact.reducerComponent("DojoMap");

let make = _children => {
  ...component,
  initialState,
  reducer,
  didMount: self =>
    Fetcher.fetchGet(
      ~url="https://immense-river-25513.herokuapp.com/locations", ~cb=data =>
      self.send(LocationsReceived(data))
    ),
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
};
