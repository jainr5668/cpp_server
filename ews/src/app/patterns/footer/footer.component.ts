import { Component, EventEmitter, Input, OnInit, Output } from "@angular/core";
import { ButtonModel } from "@patterns/button";
import { clickListenerEvent } from "@patterns/common.model";
import { FooterModel, FooterTypeEnum } from "./footer.model";

@Component({
  selector: 'pattern-footer',
  templateUrl: './footer.component.html',
})
export class FooterComponent{
  @Input() public footer: FooterModel;
  @Output() clickListener = new EventEmitter();

  onClicked(event: Event){
    if (this.footer.event) {
      this.footer.event(event);
    } else {
      this.clickListener.emit(event);
    }
  }
}