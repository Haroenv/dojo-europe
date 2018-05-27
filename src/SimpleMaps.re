[@bs.module "react-simple-maps"]
external composableMap : ReasonReact.reactClass = "ComposableMap";
[@bs.module "react-simple-maps"]
external zoomableGroup : ReasonReact.reactClass = "ZoomableGroup";
[@bs.module "react-simple-maps"]
external geographies : ReasonReact.reactClass = "Geographies";
[@bs.module "react-simple-maps"]
external geographyComponent : ReasonReact.reactClass = "Geography";
[@bs.module "react-simple-maps"]
external markers : ReasonReact.reactClass = "Markers";
[@bs.module "react-simple-maps"]
external markerComponent : ReasonReact.reactClass = "Marker";
[@bs.module "react-simple-maps"]
module ComposableMap = {
  let make = children =>
    ReasonReact.wrapJsForReason(
      ~reactClass=composableMap,
      ~props=(),
      children,
    );
};

module ZoomableGroup = {
  let make = children =>
    ReasonReact.wrapJsForReason(
      ~reactClass=zoomableGroup,
      ~props=(),
      children,
    );
};

module Geographies = {
  [@bs.deriving abstract]
  type jsProps = {geography: string};

  let make = (~geography, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=geographies,
      ~props=jsProps(~geography),
      children,
    );
};

module Geography = {
  [@bs.deriving abstract]
  type geography = {id: string};
  type projection;

  [@bs.deriving abstract]
  type jsProps = {
    geography,
    projection,
    fill: string,
    stroke: string,
    tabable: bool,
  };

  let make =
      (~geography, ~projection, ~fill, ~stroke, ~tabable=false, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=geographyComponent,
      ~props=jsProps(~geography, ~projection, ~fill, ~stroke, ~tabable),
      children,
    );
};

module Markers = {
  let make = children =>
    ReasonReact.wrapJsForReason(~reactClass=markers, ~props=(), children);
};

let invert = ((a, b)) => (b, a);

module DataMarker = {
  [@bs.deriving abstract]
  type markerT = {coordinates: (float, float)};

  [@bs.deriving abstract]
  type jsProps = {
    marker: markerT,
    tabable: bool,
  };

  let make = (~data: Fetcher.data, ~tabable=false, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=markerComponent,
      ~props=
        jsProps(
          ~marker=markerT(~coordinates=invert(Fetcher.location(data))),
          ~tabable,
        ),
      children,
    );
};
