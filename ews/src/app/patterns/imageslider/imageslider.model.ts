export class ImageSliderModel {
  id: string;
  event: any;
  imageList: ImageSliderImageModel[] = null;
  height: ImageSliderImageHeight = null;

  setImagesliderValues(
    id: string,
    imageList: ImageSliderImageModel[],
    height:ImageSliderImageHeight,
    event?: any
  ) {
    this.id = id;
    this.event = event ?? null;
    this.imageList = imageList ?? null;
    this.height = height;
  }
}
export class ImageSliderImageModel {
    src:string = null;
    link:string = null;
    constructor(src:string, link?:string){
        this.src = src;
        this.link = link;
    }
}

export enum ImageSliderImageHeight{
  SMALL = 'small',
  MEDIUM = 'medium',
  LARGE = 'large'
}