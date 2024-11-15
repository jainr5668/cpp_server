import { Component, OnInit, Input, Output, EventEmitter } from "@angular/core";
import { clickListenerEvent } from "@patterns/common.model";
import { ImageSliderImageHeight, ImageSliderModel } from "./imageslider.model";
import { Observable } from "rxjs";
import { StringIdsType } from "src/stringIds";
import { TranslateService } from "@ngx-translate/core";

@Component({
  selector: 'pattern-imageslider',
  templateUrl: './imageslider.component.html',
  styleUrls: ['./imageslider.component.css']
})
export class ImagesliderComponent implements OnInit {
  @Input() public imageslider: ImageSliderModel;

  @Output() clickListener = new EventEmitter();

  hightClass:string = 'height1';
  constructor(private translate: TranslateService) {}

  ngOnInit(){
    switch(this.imageslider.height){
      case ImageSliderImageHeight.SMALL:
        this.hightClass='height1';
        break;
      case ImageSliderImageHeight.MEDIUM:
        this.hightClass='height2';
        break;
      case ImageSliderImageHeight.LARGE:
        this.hightClass='height3';
        break;
    }
  }
  public getLocalizedString$(stringId: StringIdsType): Observable<string> {
    return this.translate.stream(stringId);
  }

  onClicked(event: Event) {
    const eventObject = new clickListenerEvent(event, this.imageslider.id);
    if (this.imageslider.event) {
      this.imageslider.event(eventObject);
    } else {
      this.clickListener.emit(eventObject);
    }
  }
  public navigateToSection(section: string) {
    window.location.hash = '';
    window.location.hash = section;
}
}

