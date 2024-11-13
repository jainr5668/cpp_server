import { ImageSliderImageHeight, ImageSliderImageModel, ImageSliderModel } from '@patterns/imageslider';

export class ProductcardModel {
  id: string;
  brand: string;
  colour: string;
  description: string;
  discount: number;
  image: ImageSliderModel;
  name: string;
  price: number;
  event: any;
  constructor(
    id: string,
    name = '',
    description = '',
    colour = '',
    brand = '',
    price = 0.0,
    discount = 0.0,
    images:string[] = [],
    event = null
  ) {
    this.id = id;
    this.brand = brand;
    this.colour = colour;
    this.description = description;
    this.discount = discount;
    this.image = new ImageSliderModel();
    let imageList = [];
    images.forEach(image => {
      imageList.push(new ImageSliderImageModel(image, '/products/' + this.id))
    })
    this.image.setImagesliderValues(
      this.id + '-image',
      imageList,
      ImageSliderImageHeight.SMALL,
      '/products/' + this.id
    );
    this.name = name;
    this.price = price;
    this.event = event;
  }
}
