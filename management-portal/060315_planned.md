# Planned Release Notes 3th June 2015
version: TBA

This is a major release that we are rolling out with many new features, updates and fixes. Help us prioritize what we work on at support.ascend.xyz

## Changes
* Platform has been updated to Azure SDK 2.6
* Tokens are renewed automatically, giving users a better experience when uploading data and running long running tasks in the portal. [ticket](http://support.ascend.xyz/forums/270649-general/suggestions/7641099-automatically-authenticate-when-oauth2-tokens-runs)
* Tiling of GeoTIffs has been added, see package description below.
* Updated all SSL Certificates to be compliant with market standards.
* When a folder is created it is automatically opened.
* Files are now sorted by name and title is displayed properly when mouse over a file.
* IE issue fixed with some background images sitting in front of everything else.
* Share Functionality implemented for AscendXYZ Tile results. Share your tiled GeoTiffs with social sites.
* Working on Draw Vector Layer Package (Preview can be requested from pks@ascend.xyz)
* Ascend Map Operators can now upload Acquisition and Map Production requests to the platform for more information.


## Packages
The following packages have been added
### Image Tiling Lens, 1.0.0-pre
Provides a lens for image tiling of GeoTiffs. 
Read more about this [here](packages/image-tiling-lens/1.0.0-pre/README.MD)

### Vector Layer Lens, 1.0.0-pre
Provides a overview lens that shows vector layers.
Read more about this [here](packages/view-vector-layer/1.0.0-pre/README.MD)

### Map Production Price Calculator, 2.0.0
The AscendXYZ Price Calculator helps partners calculate an estimated price of AscendXYZ Map Productions.
It has been updated according to a new simpler price model. If you have the old one installed you can update this from the package manager.



##Lenses
In cases that you are not familiar with our naming, a lens is a control that packages can install into the portal, such when you open a file in the Browse Files Blades you will see the lenses of all your installed packages for the given file. Let me use the Image Tiling Lens as an example:

An AscendXYZ developer is tasked to develop a tiling feature on the platform for tiling GeoTiffs into AscendXYZ WebMaps. The Program Management team decides together with the developer that the best implementation of this is by creating a Lens with the functionality of tiling GeoTiffs. For users this means that whenever they click on a GeoTiff inside the portal and opens the document blade, it will be populated with the developers Tiling Lens if and only if the user has installed the Image Tiling Lens package.

At AscendXYZ we have decided this path to ensure we can scale development without new developers has to learn our full platform stack, but simply can get started adding functionality for our users with what they already know about HTML/Javascript. 

It also ensures AscendXYZ Portal is modular and extensions can be added/updated/fixed outside our normal release cycles of the AscendXYZ Platform. 

