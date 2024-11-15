import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { ButtonModule } from '@patterns/button';
import { FooterComponent } from './footer.component';
@NgModule({
  declarations: [FooterComponent, ],
  imports: [
    CommonModule,
    ButtonModule
  ],
  exports: [FooterComponent],
})
export class FooterModule {}
